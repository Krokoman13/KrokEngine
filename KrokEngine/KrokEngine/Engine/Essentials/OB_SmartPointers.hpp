#pragma once

#include <cstddef>
#include <utility>

template<typename T>
struct contextPtr {
    T* ptr = nullptr;
    size_t counter = 0;
};

template<typename T>
class borrow_ptr {
private:
    using context = contextPtr<T>;
    mutable context* _ctx = nullptr;

    void swap(context* ctx) {
        if (_ctx) {
            _ctx->counter--;

            if (_ctx->counter == 0) {
                T* ptr = _ctx->ptr;
                _ctx->ptr = nullptr;
                delete ptr;

                delete _ctx;
            }
        }

        _ctx = ctx;

        if (_ctx) {
            _ctx->counter++;
        }
    }

public:
    borrow_ptr() = default;
    borrow_ptr(std::nullptr_t) : _ctx(nullptr) {}
    explicit borrow_ptr(context* ctx) { swap(ctx); }
    borrow_ptr(const borrow_ptr& other) { swap(other._ctx); }

    borrow_ptr(borrow_ptr&& other) noexcept { _ctx = std::move(other._ctx); other._ctx = nullptr; }
    borrow_ptr& operator=(const borrow_ptr& other) { swap(other._ctx); return *this; }
    borrow_ptr& operator=(borrow_ptr&& other) noexcept { _ctx = std::move(other._ctx); other._ctx = nullptr; return *this; }

    operator bool() const { if (_ctx) { return _ctx->ptr; } return false; }

    const T& operator*() const { return *_ctx->ptr; }
    T& operator*() { return *_ctx->ptr; }

    const T* operator->() const { return _ctx->ptr; }
    T* operator->() { return _ctx->ptr; }

    T* Get() const { return _ctx->ptr; }

    ~borrow_ptr() {
        swap(nullptr);
    }
};

template<typename T>
class owning_ptr {
private:
    using context = contextPtr<T>;
    mutable context* _ctx;

public:
    owning_ptr() = default;
    owning_ptr(std::nullptr_t) { swap(nullptr); }
    owning_ptr(T* pPtr) { swap(pPtr); }
    //template<typename... Args>
    //explicit owning_ptr(std::in_place_t, Args&&... args) {
    //    swap(new T(std::forward<Args>(args)...));
    //}
    explicit owning_ptr(const T& src) { swap(new T(src));}
    explicit owning_ptr(T&& src) { swap(new T(std::move(src))); }
    owning_ptr(const owning_ptr& other) = delete;
    owning_ptr(owning_ptr&& other) noexcept { _ctx = other._ctx; other._ctx = nullptr; }

    owning_ptr& operator=(const owning_ptr& other) = delete;
    owning_ptr& operator=(owning_ptr&& other) { _ctx = other._ctx; other._ctx = nullptr; return *this; }
    owning_ptr& operator=(std::nullptr_t) { swap(nullptr); return *this; }

    operator bool() const { if (_ctx) { return _ctx->ptr; } return false; }

    const T& operator*() const { return *_ctx->ptr; }
    T& operator*() { return *_ctx->ptr; }

    const T* operator->() const { return _ctx->ptr; }
    T* operator->() { return _ctx->ptr; }

    void swap(T* ptr) {
        if (_ctx) {
            if (_ctx->ptr) {
                delete _ctx->ptr;
            }

            if (_ctx->counter == 1) {
                _ctx->ptr = ptr;
                return;
            }
            else {
                _ctx->counter--;
            }
        }

        _ctx = new context();
        _ctx->counter++;

        _ctx->ptr = ptr;
    }

    T* Get() const { return _ctx->ptr; }

    template<typename Y>
    borrow_ptr<Y> TryCast()
    {
        static_assert(std::is_base_of<T, Y>::value, "Y must be a derived class of T");

        Y* newPointer = dynamic_cast<Y*>(_ctx->ptr);

        if (newPointer == nullptr) {
            return borrow_ptr<Y>();
        }

        contextPtr<Y>* outCon = new contextPtr<Y>();
        outCon->ptr = newPointer;
        outCon->counter = _ctx->counter;
        return borrow_ptr<Y>(outCon);
    }

    borrow_ptr<T> borrow() { return borrow_ptr<T>(_ctx); }
    const borrow_ptr<T> borrow() const { return borrow_ptr<T>(_ctx); }

    void destroy() { swap(nullptr); }

    ~owning_ptr() {
        if (_ctx) {
            _ctx->counter--;
            T* ptr = _ctx->ptr;

            if (_ctx->counter == 0) {
                delete _ctx;
            }

            if (_ctx->ptr) {
                _ctx->ptr = nullptr;
                delete ptr;
            }
        }
    }
};