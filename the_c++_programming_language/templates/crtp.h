#pragma once

#include <cstdint>
#include <iostream>

class DynBase {
 public:
  virtual uint64_t get_value() const = 0;
  virtual void tick(uint64_t n) = 0;
};

class DynDerived : public DynBase {
 public:
  DynDerived() : counter(0) {
  }

  uint64_t get_value() const override {
    return counter;
  }

  void tick(uint64_t n) override {
    counter += n;
  }

 private:
  uint64_t counter;
};

template <typename T>
class CRTP {
 public:
  uint64_t get_value() const {
    return impl()->get_value();
  }

  void tick(uint64_t n) {
    return impl()->tick(n);
  }

 private:
  T* impl() {
    return static_cast<T*>(this);
  }
  const T* impl() const {
    return static_cast<const T*>(this);
  }

  CRTP() {
  }
  friend T;
};

class Derived : public CRTP<Derived> {
 public:
  Derived() : counter(0) {
  }

  uint64_t get_value() const {
    return counter;
  }

  void tick(uint64_t n) {
    counter += n;
  }

 private:
  uint64_t counter;
};

/*
// typo still compiled and runned, but wrong calling of method
class Derived1 : public CRTP<Derived> {
 public:
  Derived1() : counter(0) {}

  uint64_t get_value() const {
    return counter;
  }

  void tick(uint64_t n) {
    counter += n;
  }

 private:
  uint64_t counter;
};
*/

template <typename T>
class CommonFuncClass {
 public:
  void scale(double ratio);
  void square();
  void set_opposite();

 private:
  T* impl() {
    return static_cast<T*>(this);
  }
  const T* impl() const {
    return static_cast<const T*>(this);
  }

  CommonFuncClass() = default;
  friend T;
};

template <typename T>
void CommonFuncClass<T>::scale(double ratio) {
  impl()->set_value(impl()->get_value() * ratio);
}

template <typename T>
void CommonFuncClass<T>::square() {
  impl()->set_value(impl()->get_value() * impl()->get_value());
}

template <typename T>
void CommonFuncClass<T>::set_opposite() {
  impl()->set_value(impl()->get_value() * -1);
}

class PartConcreteA : public CommonFuncClass<PartConcreteA> {
 public:
  PartConcreteA(double value) : value_(value) {
  }

  double get_value() const {
    return value_;
  }
  void set_value(double value) {
    value_ = value;
  }

 private:
  double value_;
};

class PartConcreteB : public CommonFuncClass<PartConcreteB> {
 public:
  PartConcreteB(double value) : value_(value) {
  }

  double get_value() const {
    return value_;
  }
  void set_value(double value) {
    value_ = value;
  }

 private:
  double value_;
};