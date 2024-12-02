#ifndef COMPLEX_ARRAY_HPP
#define COMPLEX_ARRAY_HPP

#include <cstddef>

class ComplexArray
{
public:
  ComplexArray(const ComplexArray&);
  ComplexArray(ComplexArray&&) noexcept;
  ComplexArray& operator=(const ComplexArray&);
  ComplexArray& operator=(ComplexArray&&) noexcept;
  ComplexArray(size_t, double, double);
  ~ComplexArray() { clear(); }

  size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  void clear() noexcept;
  void swap(ComplexArray&) noexcept;

private:
  size_t size_ = 0;
  size_t capacity_;
  double* real_;
  double* imag_;
};

#endif

