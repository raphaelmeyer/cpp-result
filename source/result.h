#pragma once

#include <variant>
#include <type_traits>

namespace rm {

template<typename OkType, typename ErrType>
class Result
{
public:
  Result() = default;

  template <typename T, typename std::enable_if<
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
};

} // namespace ns
