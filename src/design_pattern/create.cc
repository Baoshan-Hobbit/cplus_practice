/*************************************************************************
  > File Name: factory.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月10日 星期二 16时08分22秒
 ************************************************************************/

#include "src/design_pattern/create.h"
#include <memory>
#include "src/design_pattern/product.h"

AbstractProduct* SimpleFactory::CreateProduct(int arg) {
  AbstractProduct* abstract_product(nullptr);
  switch (arg) {
    case 1:
      abstract_product = new Product1("product1");
      break;
    case 2:
      abstract_product = new Product2("product2");
      break;
    default:
      break;
  }
  return abstract_product;
}

AbstractProduct* Factory1::CreateProduct() {
  return new Product1("product1");
}
AbstractProduct* Factory2::CreateProduct() {
  return new Product2("product2");
}

// deprecated
//std::shared_ptr<AbstractProduct> SimpleFactory::CreateProduct(int arg) {
//  // shared_ptr要声明后再使用,避免直接在参数或返回值中实例化,
//  // 类似于指针先声明后赋值
//  // 如 return std::make_shared<AbstractProduct>()是非法的,
//  // 因为接口不能被实例化
//  std::shared_ptr<AbstractProduct> product; // 类似nullptr
//  switch (arg) {
//    case 1:
//      product = std::make_shared<Product1>("product1");
//      break; 
//    case 2:
//      product = std::make_shared<Product2>("product2");
//      break;
//    default:
//      break;
//  }
//  return product;
//}

//std::shared_ptr<AbstractProduct> Factory1::CreateProduct() {
//  return std::make_shared<Product1>("product1");
//}
//
//std::shared_ptr<AbstractProduct> Factory2::CreateProduct() {
//  return std::make_shared<Product2>("product2");
//}

bool ConcreteBuilder::MakeFood() {
  humbger_->set_food("chicken");
  return true;
}
bool ConcreteBuilder::MakeDrink() {
  if (humbger_->get_food() != "chicken") return false;
  humbger_->set_drink("cola");
  return true;
}

ConcretePrototype* ConcretePrototype::Clone() {
  ConcretePrototype* obj = new ConcretePrototype();
  obj->set_big_element(big_element_);
  obj->set_type(type_);
  return obj;
}
