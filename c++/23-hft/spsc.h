#pragma once

template <typename T, size_t Capacity>
class SPSCQueue {
  public:
    bool try_push(const T& data);
    bool try_push(T&& data);
    bool try_pop(T& data);
    auto size() const noexcept -> size_t;

  private:
    alignas(64) T buffer[Capacity];
    alignas(64) size_t head = 0;
    alignas(64) size_t tail = 0;
};
