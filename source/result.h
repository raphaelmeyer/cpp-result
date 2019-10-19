#pragma once

namespace rm {

template<typename OkType, typename ErrType>
class Result
{
public:
  ErrType const & err() const { return _value; }

  bool is_err() const { return true; }
  bool is_ok() const { return false; }

private:
  std::string const _value = "";
};

} // namespace ns
