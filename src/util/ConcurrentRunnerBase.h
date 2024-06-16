//
// Created by navid on 05/09/2021.
//

/*
#ifndef DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H
#define DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <thread>

// Object that runs multiple functions, each in its own thread, starting them as simultaneously as possible.
class ConcurrentRunner final
        {
        public:
            template<typename... BackgroundThreadsFunctions>
            explicit ConcurrentRunner(const std::function<void()>& this_thread_function, const BackgroundThreadsFunctions&... background_threads_functions)
            : _this_thread_function{this_thread_function}
            , _num_threads_total{1 + sizeof...(BackgroundThreadsFunctions)}
            {
                this->PrepareBackgroundThreads({ background_threads_functions... });
            }


            // Executes `ThreadProc` for this thread's function and waits for all of the background threads to finish.
            void run()
            {
                this->ThreadProc(_this_thread_function);

                for (auto& background_thread : _background_threads)
                    background_thread.join();
            }

            void add(std::function<void()> f) {
                _background_threads.emplace_back([this, function = f]()
                {
                    this->ThreadProc(function);
                });
                _num_threads_total ++;
            }

        private:
            // Creates the background threads: each of them will execute `ThreadProc` with its respective function.
            void PrepareBackgroundThreads(const std::vector<std::function<void()>>& background_threads_functions)
            {
                // Iterate through the vector of the background threads' functions and create a new thread with `ThreadProc` for each of them.
                _background_threads.reserve(background_threads_functions.size());
                for (const auto& background_thread_function : background_threads_functions)
                {
                    _background_threads.emplace_back([this, function = background_thread_function]()
                    {
                        this->ThreadProc(function);
                    });
                }
            }

            // Procedure that will be executed by each thread, including the "main" thread and all background ones.
            void ThreadProc(const std::function<void()>& function)
            {
                // Increment the `_num_threads_waiting_for_start_signal` while the mutex is locked, thus signalizing that a new thread is ready to start.
                std::unique_lock<std::mutex> lock{_mutex};
                ++_num_threads_waiting_for_start_signal;
                const bool ready_to_go = (_num_threads_waiting_for_start_signal == _num_threads_total);
                lock.unlock();

                if (ready_to_go)
                {
                    // If this thread was the last one of the threads which must start simultaneously, notify all other threads that they are ready to start.
                    _cv.notify_all();
                }
                else
                {
                    // If this thread was not the last one of the threads which must start simultaneously, wait on `_cv` until all other threads are ready.
                    lock.lock();
                    _cv.wait(lock, [this]()
                    {
                        return (_num_threads_waiting_for_start_signal == _num_threads_total);
                    });
                    lock.unlock();
                }

                // Execute this thread's internal function.
                function();
            }

        private:
            std::function<void()> _this_thread_function;
            std::vector<std::thread> _background_threads;

            unsigned int _num_threads_total;
            unsigned int _num_threads_waiting_for_start_signal{0}; // counter of the threads which are ready to send running their functions
            mutable std::mutex _mutex; // mutex that protects the counter
            std::condition_variable _cv; // waited on by all threads but the last one; notified when the last thread increments the counter
        };

#endif //DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H
*/
#ifndef DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H
#define DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H

#include <tuple>
#include <vector>
#include <type_traits>
#include <utility>

#define M 3
#define TYPE void(void)

namespace Detail
{
    template<typename Tuple, typename Function, std::size_t... I>
    constexpr void ForEachTupleElement(Tuple&& tuple, Function function, std::index_sequence<I...>)
    {
        int dummy[] = { 0, (((void)(function(std::get<I>(std::forward<Tuple>(tuple))))), 0)... };
        (void)dummy;
    }
}

// Applies a given function (typically - with a template operator(), e.g., a generic lambda) to each element of a tuple.
template<typename Tuple, typename Function, std::size_t... I>
constexpr void ForEachTupleElement(Tuple&& tuple, Function function)
{
    Detail::ForEachTupleElement(std::forward<Tuple>(tuple), function,
                                std::make_index_sequence<std::tuple_size_v<std::remove_cv_t<std::remove_reference_t<Tuple>>>>{});
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

#include <mutex>
#include <condition_variable>
#include <array>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>

// Common non-template part of the `ConcurrentRunner` implementation.
class ConcurrentRunnerBase
{
protected:
    inline ConcurrentRunnerBase() = default;
    inline ~ConcurrentRunnerBase() = default;

protected:
    unsigned int _num_threads_waiting_for_start_signal{0}; // protected by `mutex`
    mutable std::mutex _mutex;
    std::condition_variable _cv; // waited on by all threads but the last one; notified when the last thread increments the counter
};

// Object that runs multiple functions, each in its own thread, starting them as simultaneously as possible.
template<typename ThisThreadFunction, std::size_t NumberOfBackgroundThreads>
class ConcurrentRunner final : private ConcurrentRunnerBase
{
public:
    int f() {
       return sizeof(*this);
    };
    template<typename ThisThreadFunctionArg, typename... BackgroundThreadsFunctions>
    explicit ConcurrentRunner(ThisThreadFunctionArg&& this_thread_function, BackgroundThreadsFunctions&&... background_threads_functions)
            : _this_thread_function{std::forward<ThisThreadFunctionArg>(this_thread_function)}
    {
        static_assert(sizeof...(BackgroundThreadsFunctions) == NumberOfBackgroundThreads);
        this->Prepare(std::forward<BackgroundThreadsFunctions>(background_threads_functions)...);
        this->Run();
    }

    ConcurrentRunner(const ConcurrentRunner&) = delete;
    ConcurrentRunner& operator=(const ConcurrentRunner&) = delete;

    // Executes `ThreadProc` for this thread's function and waits for all of the background threads to finish.
    void Run()
    {
        this->ThreadProc(std::move(_this_thread_function));

        for (auto& background_thread : _background_threads)
            background_thread.join();
    }

private:
    // Creates the background threads: each of them will execute `ThreadProc` with its respective function.
    template<typename... BackgroundThreadsFunctions>
    void Prepare(BackgroundThreadsFunctions&&... background_threads_functions)
    {
        // Copies of the argument functions (created by move constructors where possible), collected in a tuple.
        std::tuple<std::decay_t<BackgroundThreadsFunctions>...> background_threads_functions_tuple{
                std::forward<BackgroundThreadsFunctions>(background_threads_functions)...
        };

        // Iterate through the tuple of the background threads' functions and create a new thread with `ThreadProc` for each of them.
        unsigned int index_in_array = 0;
        ForEachTupleElement(std::move(background_threads_functions_tuple), [this, &index_in_array](auto&& function)
        {
            auto i = index_in_array++;
            _background_threads[i] = std::thread{[this, function = std::move(function)]() mutable
                                                 {
                                                     this->ThreadProc(std::move(function));
                                                 }};
        });
    }

    // Procedure that will be executed by each thread, including the "main" thread and all background ones.
    template<typename Function>
    void ThreadProc(Function&& function)
    {
        // Increment the `_num_threads_waiting_for_start_signal` while the mutex is locked, thus signalizing that a new thread is ready to send.
        std::unique_lock lock{_mutex};
        ++_num_threads_waiting_for_start_signal;
        const bool ready_to_go = (_num_threads_waiting_for_start_signal == (1 + NumberOfBackgroundThreads));
        lock.unlock();

        if (ready_to_go)
        {
            // If this thread was the last one of the threads which must start simultaneously, notify all other threads that they are ready to send.
            _cv.notify_all();
        }
        else
        {
            // If this thread was not the last one of the threads which must send simultaneously, wait on `_cv` until all other threads are ready.
            lock.lock();
            _cv.wait(lock, [this]() noexcept -> bool
            {
                return (_num_threads_waiting_for_start_signal == (1 + NumberOfBackgroundThreads));
            });
            lock.unlock();
        }

        // Execute this thread's internal function.
        std::forward<Function>(function)();
    }

private:
    ThisThreadFunction _this_thread_function;
    std::array<std::thread, NumberOfBackgroundThreads> _background_threads;
};

template<typename T, typename... U>
ConcurrentRunner(T&&, U&&...) -> ConcurrentRunner<std::decay_t<T>, sizeof...(U)>;

class Encap {
public :
    explicit Encap(unsigned int f):_f(f) {};
    template<typename ThisThreadFunctionArg, typename... BackgroundThreadsFunctions>
    void operator()(ThisThreadFunctionArg&& this_thread_function, BackgroundThreadsFunctions&&... background_threads_functions)
    {_runner = new ConcurrentRunner<std::decay_t<ThisThreadFunctionArg>, sizeof...(BackgroundThreadsFunctions)>(this_thread_function, background_threads_functions...);};
    ~Encap() {free(_runner);}
private :
    unsigned int _f = 0;
    void* _runner= (void *)malloc(8*(_f+1) + 48);

};


template <std::size_t... Is>
auto create_tuple_impl(std::index_sequence<Is...>, const std::vector<std::function<TYPE>>& arguments) {
    return std::make_tuple(arguments[Is]...);
}

template<std::size_t N>
auto create_tuple(const std::vector<std::function<TYPE>> &arguments) {
    return create_tuple_impl(std::make_index_sequence<N>{}, arguments);
}

#endif //DICE_GAME_PROJECT_CONCURRENTRUNNERBASE_H