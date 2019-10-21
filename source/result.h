#pragma once

#include <variant>

namespace rm {

template<typename OkType, typename ErrType>
class Result
{
public:
  static_assert(not std::is_same<OkType, ErrType>::value,
    "Result and Error type must be different");

  Result() : _value{} {}

  Result(ErrType value) : _value{std::move(value)} {}
  Result(OkType value) : _value{std::move(value)} {}

  ErrType const & err() const { return std::get<ErrType>(_value); }
  OkType const & ok() const { return std::get<OkType>(_value); }

  bool is_err() const { return std::holds_alternative<ErrType>(_value); }
  bool is_ok() const { return std::holds_alternative<OkType>(_value); }

private:
  std::variant<ErrType, OkType> _value;
};

} // namespace ns
