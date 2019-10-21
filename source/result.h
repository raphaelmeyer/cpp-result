#pragma once

#include <variant>
#include <type_traits>

namespace rm {

template<typename OkType, typename ErrType>
auto make_ok(OkType value);

template<typename OkType, typename ErrType>
auto make_err(ErrType value);

template<typename OkType, typename ErrType>
class Result
{
public:
  Result() = default;

  template<typename T, typename std::enable_if<
    std::is_convertible<T, std::variant<ErrType, OkType>>{}, int>::type = 0>
  Result(T && value) : _value{std::forward<T>(value)} {}

  ErrType const & err() const { return std::get<err_index>(_value); }
  OkType const & ok() const { return std::get<ok_index>(_value); }

  bool is_err() const { return _value.index() == err_index; }
  bool is_ok() const { return _value.index() == ok_index; }

private:
  constexpr static std::size_t const err_index = 0;
  constexpr static std::size_t const ok_index = 1;
  std::variant<ErrType, OkType> _value;

  Result(std::variant<ErrType, OkType> value) : _value{std::move(value)} {}

  friend auto make_ok<OkType, ErrType>(OkType value);
  friend auto make_err<OkType, ErrType>(ErrType value);
};

template<typename OkType, typename ErrType>
auto make_ok(OkType value) {
  using T = Result<OkType, ErrType>;
  return T{std::variant<ErrType, OkType>{std::in_place_index<T::ok_index>, std::move(value)}};
}

template<typename OkType, typename ErrType>
auto make_err(ErrType value) {
  using T = Result<OkType, ErrType>;
  return T{std::variant<ErrType, OkType>{std::in_place_index<T::err_index>, std::move(value)}};
}

} // namespace ns
