#include "complex_array.hpp"
#include <memory>
#include <utility>

ComplexArray::ComplexArray(size_t size, double re, double im) :
  capacity_(size),
  real_(static_cast<double*>(operator new(sizeof(double) * capacity_))),
  imag_(static_cast<double*>(operator new(sizeof(double) * capacity_)))
{
  for (; size_ != size; ++size_) {
    new (real_ + size_) double(re);
    new (imag_ + size_) double(im);
  }
}

ComplexArray::ComplexArray(const ComplexArray& rhs) :
  capacity_(rhs.size_),
  real_(static_cast<double*>(operator new(sizeof(double) * capacity_))),
  imag_(static_cast<double*>(operator new(sizeof(double) * capacity_)))
{
  std::uninitialized_copy(rhs.imag_, rhs.imag_ + size_, imag_);
  std::uninitialized_copy(rhs.real_, rhs.real_ + size_, real_);
  size_ = rhs.size_;
}

ComplexArray::ComplexArray(ComplexArray&& rhs) noexcept :
  size_(std::exchange(rhs.size_, 0)),
  capacity_(std::exchange(rhs.capacity_, 0)),
  real_(std::exchange(rhs.real_, nullptr)),
  imag_(std::exchange(rhs.imag_, nullptr))
{
}

ComplexArray& ComplexArray::operator=(const ComplexArray& rhs)
{
  ComplexArray tmp = rhs;
  swap(tmp);
  return *this;
}

ComplexArray& ComplexArray::operator=(ComplexArray&& rhs) noexcept
{
  clear();
  size_ = std::exchange(rhs.size_, 0);
  capacity_ = std::exchange(rhs.capacity_, 0);
  real_ = std::exchange(rhs.real_, nullptr);
  imag_ = std::exchange(rhs.imag_, nullptr);
  return *this;
}

void ComplexArray::swap(ComplexArray& rhs) noexcept
{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(real_, rhs.real_);
  std::swap(imag_, rhs.imag_);
}

void ComplexArray::clear() noexcept
{
  std::destroy(real_, real_ + size_);
  std::destroy(imag_, imag_ + size_);
  operator delete(std::exchange(real_, nullptr));
  operator delete(std::exchange(imag_, nullptr));
  capacity_ = 0;
  size_ = 0;
}

