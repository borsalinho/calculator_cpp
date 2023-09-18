#include "calcValidator.h"

namespace s21 {

std::string& CalcValidator::Validation(std::string& str) {
  DelSpace(str);

  if (!CheckLenght(str))
    return err_ = "The number of common characters must be less than 255";
  if (!CheckNumber(str)) return err_ = "Missing number";
  if (!CheckSymvols(str)) return err_ = "Invalid values ​​found";
  if (!CheckOperAndNum(str)) return err_ = "Missing operand";
  if (!CheckBracer(str)) return err_ = "Empty parenthesis found";
  if (!CheckBracerCount(str)) return err_ = "Missing parenthesis";
  if (!CheckDotAndExp(str)) return err_ = "Extra dot or expander";

  return err_;
}

void CalcValidator::DelSpace(std::string& str) {
  size_t i = 0;
  int j = 0;
  while (i < str.size()) {
    if (str[i] == ' ') {
      i++;
    } else {
      str[j] = str[i];
      i++;
      j++;
    }
  }
  str[j] = 0;
}

bool CalcValidator::CheckLenght(const std::string& str) {
  if (str.size() <= max_size_) return true;
  return false;
}

bool CalcValidator::CheckSymvols(std::string str) {
  int flag = 1;

  while (flag != 0) {
    flag = 0;
    for (auto& q : tokens_) {
      std::string::size_type pos = str.find(q);
      if (pos != std::string::npos) {
        str.erase(pos, q.length());
        if (str.size() == 0) return true;
        flag = 1;
        break;
      }
    }
  }

  return false;
}

bool CalcValidator::CheckNumber(const std::string& str) {
  size_t i = 0;
  while (i < str.size()) {
    if (str[i] == 'x') return true;
    if ((str[i] >= 48 && str[i] <= 57)) return true;
    if (str[i] == 'p') {
      i++;
      if (str[i] == 'i') {
        i++;
        return true;
      }
    }
    if (str[i] == 'i') {
      i++;
      if (str[i] == 'n') {
        i++;
        if (str[i] == 'f') {
          i++;
          return true;
        }
      }
    }
    i++;
  }
  return false;
}

bool CalcValidator::CheckOperAndNum(const std::string& str) {
  size_t i = 0;

  if (str[i] == '-' || str[i] == '+' || str[i] == '(') {
    i++;
  }

  for (; i < str.size(); i++) {
    if ((str[0] == '^' || str[0] == '%' || str[0] == '/' || str[0] == '*'))
      return false;

    if ((str[i] == '^' || str[i] == '%' || str[i] == '/' || str[i] == '*') &&
        (!IsPrefCharDigit(str[i - 1]) || !IsNextCharValid(str[i + 1])))
      return false;

    if ((str[i] == '-' || str[i] == '+') &&
        (!IsPrefCharValid(str[i - 1]) || !IsNextCharValid(str[i + 1])))
      return false;

    if (str[i] == '(' && !IsPrevOperValue(str[i - 1])) return false;

    if (str[i] == ')' && i != str.size() - 1 && !IsNextOperValue(str[i + 1]) &&
        str[i + 1] != ')')
      return false;
  }

  return true;
}

int CalcValidator::CheckBracer(const std::string& str) {
  int status = 1;
  size_t i = 0;

  while (i < str.size() && status) {
    if (str[i] == '(' && str[i + 1] == ')') status = 0;
    i++;
  }

  return status;
}

int CalcValidator::CheckBracerCount(const std::string& str) {
  int status = 1;
  size_t i = 0;
  int br_open = 0;
  int br_close = 0;

  while (i < str.size()) {
    if (str[i] == '(') br_open++;
    if (str[i] == ')') br_close++;
    i++;
  }

  if (br_open != br_close) status = 0;

  return status;
}

int CalcValidator::CheckDotAndExp(const std::string& str) {
  int status = 1;
  size_t i = 0;

  while (i < str.size() && status) {
    if ((str[i] >= 48 && str[i] <= 57)) {
      int exp = 0;
      int dot = 0;
      while ((str[i] >= 48 && str[i] <= 57) || str[i] == '.' || str[i] == 'e') {
        i++;
        if (str[i] == 'e') {
          if (str[i + 1] == 0) status = 0;
          if (exp) status = 0;
          exp = 1;
        } else if (str[i] == '.') {
          if (dot || exp) status = 0;
          dot = 1;
        }
      }
    }
    if (str[i] == '.') {
      if (i == 0)
        status = 0;
      else {
        if (str[i - 1] < 48 || str[i - 1] > 57) status = 0;
        if (str[i + 1] < 48 || str[i + 1] > 57) status = 0;
      }
    }
    i++;
  }
  return status;
}

bool CalcValidator::IsPrevOperValue(char i) {
  if (IsNextOperValue(i) || i == '(' || i == 'n' || i == 'g' || i == 's' ||
      i == 't')
    return true;
  return false;
}

bool CalcValidator::IsNextOperValue(char i) {
  if (i == '-' || i == '+' || i == '*' || i == '/' || i == '^' || i == '%')
    return true;
  return false;
}

bool CalcValidator::IsPrefCharDigit(char i) {
  if ((i >= 48 && i <= 57) || i == ')' || i == 'x' || i == 'f' || i == '.' ||
      i == 'i')
    return true;
  return false;
}

bool CalcValidator::IsNextCharValid(char i) {
  if ((i >= 48 && i <= 57) || i == '(' || i == 'x' || i == 'i' || i == 'c' ||
      i == 'l' || i == 'a' || i == 's' || i == 't' || i == 'p')
    return true;
  return false;
}

bool CalcValidator::IsPrefCharValid(char i) {
  if (IsPrefCharDigit(i) || i == '(' || i == 'e') return true;
  return false;
}

void CalcValidator::UpMaxSize() { max_size_ = max_size_ + 2; }

std::string& CalcValidator::GetError() { return err_; }

void CalcValidator::SetErrDefault() { err_ = "no_err"; }

} // namespace s21
