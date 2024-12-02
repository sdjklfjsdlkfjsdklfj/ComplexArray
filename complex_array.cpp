#include "complex_array.hpp"
#include <memory>
#include <utility>

ComplexArray::ComplexArray(size_t size, double re, double im) :
  capacity_(size),
  real_(static_cast<double*>(operator new(sizeof(double) * capacity_))),
  imag_(static_cast<double*>(operator new(sizeof(double) * capacity_)))
{
  std::fill(real_, real_ + size, re);
  std::fill(imag_, imag_ + size, im);
  size_ = size;
}

ComplexArray::ComplexArray(const ComplexArray& rhs) :
  capacity_(rhs.size_),
  real_(static_cast<double*>(operator new(sizeof(double) * capacity_))),
  imag_(static_cast<double*>(operator new(sizeof(double) * capacity_)))
{
  std::uninitialized_copy(rhs.imag_, rhs.imag_ + rhs.size_, imag_);
  std::uninitialized_copy(rhs.real_, rhs.real_ + rhs.size_, real_);
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
  if (capacity_ < rhs.capacity_) {
    ComplexArray tmp = rhs;
    swap(tmp);
    return *this;
  }
  std::destroy(real_, real_ + size_);
  std::destroy(imag_, imag_ + size_);
  std::uninitialized_copy(rhs.imag_, rhs.imag_ + rhs.size_, imag_);
  std::uninitialized_copy(rhs.real_, rhs.real_ + rhs.size_, real_);
  size_ = rhs.size_;
  return *this;
}

ComplexArray& ComplexArray::operator=(ComplexArray&& rhs) noexcept
{
  swap(rhs);
  return *this;
}

ComplexArray::~ComplexArray()
{
  std::destroy(real_, real_ + size_);
  std::destroy(imag_, imag_ + size_);
  operator delete(real_);
  operator delete(imag_);
}

void ComplexArray::swap(ComplexArray& rhs) noexcept
{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(real_, rhs.real_);
  std::swap(imag_, rhs.imag_);
}

void ComplexArray::resize(size_t size, double re, double im)
{
  if (size == size_) {
    return;
  }
  if (size < size_) {
    std::destroy(real_ + size, real_ + size_);
    std::destroy(imag_ + size, imag_ + size_);
    size_ = size;
    return;
  }
  if (size <= capacity_) {
    std::fill(real_ + size_, real_ + size, re);
    std::fill(imag_ + size_, imag_ + size, im);
    size_ = size;
    return;
  }
  ComplexArray tmp(size, re, im);
  std::destroy(tmp.real_, tmp.real_ + size_);
  std::destroy(tmp.imag_, tmp.imag_ + size_);
  std::uninitialized_copy(imag_, imag_ + size_, tmp.imag_);
  std::uninitialized_copy(real_, real_ + size_, tmp.real_);
  swap(tmp);
}

