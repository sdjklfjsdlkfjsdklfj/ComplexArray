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
  ~ComplexArray();

  void resize(size_t, double, double);

  size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  const double& real_at(size_t i) const { return real_[i]; }
  const double& imag_at(size_t i) const { return imag_[i]; }
  double& real_at(size_t i) { return real_[i]; }
  double& imag_at(size_t i) { return imag_[i]; }

  void swap(ComplexArray&) noexcept;

private:
  size_t size_ = 0;
  size_t capacity_;
  double* real_;
  double* imag_;
};

#endif

