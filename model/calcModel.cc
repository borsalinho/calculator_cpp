// #include "calcModel.h"

// namespace s21 {

// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //================= CALCUL==============================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================

// CalcModel::CalcModel(std::string str) {
//   if (Validation(str) == "no_err") {
//     Parser(str);
//     Calculation();
//   }
// };

// double CalcModel::Calculation() {
//   std::stack<double> buffer_number_{};
//   std::stack<t_operator> buffer_operator_{};
//   int out = 800;
//   t_operator zero{};

//   zero.priority = -1;
//   zero.value = out;
//   buffer_operator_.push(zero);

//   while (stack_operator_.top().value != out ||
//          buffer_operator_.top().value != out) {
//     if (stack_operator_.top().value == 90) {
//       TopPopOper();
//       Calculation();
//       TopPopOper();
//     } else {
//       Minusization();
//       if (buffer_operator_.top().priority > stack_operator_.top().priority) {
//         stack_number_.push(LocalArifm(buffer_number_.top(), TopPopNum(),
//                                       buffer_operator_.top().value));
//         buffer_number_.pop();
//         buffer_operator_.pop();
//       } else {
//         t_operator uppr_oprtr = TopPopOper();
//         t_operator lowr_oprtr = stack_operator_.top();
//         double uppr_num = TopPopNum();
//         if (uppr_oprtr.priority <= lowr_oprtr.priority) {
//           if (uppr_oprtr.priority == 3 && lowr_oprtr.priority == 3) {
//             LocalCalc(uppr_num, uppr_oprtr.value);
//           } else {
//             buffer_number_.push(uppr_num);
//             buffer_operator_.push(uppr_oprtr);
//           }
//         } else LocalCalc(uppr_num, uppr_oprtr.value);
//       }
//     }
//    if (std::isnan(stack_number_.top())) return answer_ = stack_number_.top();
//   }
//   return answer_ = stack_number_.top();
// }

// t_operator CalcModel::TopPopOper() {
//   t_operator oprtr = stack_operator_.top();
//   stack_operator_.pop();
//   return oprtr;
// }

// double& CalcModel::TopPopNum() {
//   double& num = stack_number_.top();
//   stack_number_.pop();
//   return num;
// }

// void CalcModel::Minusization() {
//   t_operator plus{};
//   plus.priority = 1;
//   plus.value = 1;
//   if (stack_operator_.top().value == 2) {
//     TopPopOper();
//     stack_operator_.push(plus);
//     stack_number_.push(TopPopNum() * (-1));
//   }
// }

// double CalcModel::LocalArifm(double& uppr_num, double& lowr_num, int& oprtr) {
//   double answer{0};
//   switch (oprtr) {
//     case 1:
//       answer = lowr_num + uppr_num;
//       break;
//     case 2:
//       answer = lowr_num - uppr_num;
//       break;
//     case 3:
//       answer = lowr_num * uppr_num;
//       break;
//     case 4:
//       answer = lowr_num / uppr_num;
//       break;
//     case 5:
//       answer = fmod(lowr_num, uppr_num);
//       break;
//     case 6:
//       answer = pow(lowr_num, uppr_num);
//       break;
//   }
//   return answer;
// }

// void CalcModel::LocalCalc(double& uppr_num, int& oprtr) {
//   if (IsTrigonometric(oprtr)) 
//     stack_number_.push(LocalTrignm(uppr_num, oprtr));
//   else 
//     stack_number_.push(LocalArifm(uppr_num, TopPopNum(), oprtr));
// }

// bool CalcModel::IsTrigonometric(int& oprtr) {
//   if (oprtr >= 10 && oprtr < 19) return true;
//   return false;
// }


// double CalcModel::LocalTrignm(double& num, int& oprtr) {
//   switch (oprtr) {
//     case 10: return cos(num);

//     case 11: return sqrt(num);

//     case 12: return sin(num);

//     case 13: return tan(num);

//     case 14: return acos(num);

//     case 15: return asin(num);

//     case 16: return atan(num);

//     case 17: return log(num);

//     case 18: return log10(num);
//   }
//   return 0;
// }

// double& CalcModel::GetResult() { return answer_; };

// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //================= PARSER==============================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================

// void CalcModel::Parser(std::string& str) {
//   t_operator zero{};
//   zero.priority = -1;
//   zero.value = 800;

//   stack_operator_.push(zero);

//   for (size_t i = 0; i < str.size();) {
//     if (MyIsDigit(str[i])) {
//       double numb_d_;

//       if (IsDigitDotExp(str[i])) {
//         std::string numb_s_ = {};

//         while (IsDigitDotExp(str[i])) {
//           numb_s_.push_back(str[i++]);
//           if (str[i - 1] == 'e' && (str[i] == '-' || str[i] == '+'))
//             numb_s_.push_back(str[i++]);
//         }
        
//         numb_d_ = std::stod(numb_s_.c_str());
//       } else {
//         if (str[i] == 'p')
//           numb_d_ = M_PI;
//         else {
//           i++;
//           numb_d_ = INFINITY;
//         }
//         i = i + 2;
//       }
      
//       stack_number_.push(numb_d_);
//     } else {
//       if (IsOperator(str[i])) {
//         if ((str[i] == '-' || str[i] == '+') && (str[i - 1] == '(' || i == 0))
//           stack_number_.push(0);
//         stack_operator_.push(IdentOperator(str[i++]));

//       } else stack_operator_.push(IdentFunc(str, i));
//     }
//   }
// }

// bool CalcModel::MyIsDigit(char c) {
//   if ((IsDigitDotExp(c)) || (c == 'i') || (c == 'p')) return true;
//   return false;
// }

// bool CalcModel::IsDigitDotExp(char c) {
//   if ((std::isdigit(c)) || (c == 'e') || (c == '.')) return true;
//   return false;
// }

// bool CalcModel::IsOperator(char c) {
//   if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' ||
//       c == '(' || c == ')')
//     return true;
//   return false;
// }

// t_operator CalcModel::IdentOperator(char c) {
//   t_operator operator_{};
//   switch (c) {
//     case '+':
//       AssignValuePriory(1, 1, operator_);
//       break;
//     case '-':
//       AssignValuePriory(1, 2, operator_);
//       break;
//     case '*':
//       AssignValuePriory(2, 3, operator_);
//       break;
//     case '/':
//       AssignValuePriory(2, 4, operator_);
//       break;
//     case '%':
//       AssignValuePriory(2, 5, operator_);
//       break;
//     case '^':
//       AssignValuePriory(3, 6, operator_);
//       break;
//     case ')':
//       AssignValuePriory(90, 90, operator_);
//       break;
//     case '(':
//       AssignValuePriory(0, 800, operator_);
//       break;
//   }
//   return operator_;
// }

// void CalcModel::AssignValuePriory(int p, int v, t_operator& t) {
//   t.priority = p;
//   t.value = v;
// }

// t_operator CalcModel::IdentFunc(std::string str, size_t& i) {
//   t_operator operator_{};

//   std::string buff;
//   while(IsTrigoChar(str[i])){
//     buff.push_back(str[i++]);
//     for (auto& q : functions_){
//       if (q.str == buff){
//         AssignValuePriory(q.p, q.v, operator_);
//         break;
//       }
//     }
//   }

//   return operator_;
// }


// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //================= VALIDATOR==============================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================

// std::string& CalcModel::Validation(std::string& str) {
//   DelSpace(str);

//   if (!CheckLenght(str))
//     return err_ = "The number of common characters must be less than 255";
//   if (!CheckNumber(str)) return err_ = "Missing number";
//   if (!CheckSymvols(str)) return err_ = "Invalid values ​​found";
//   if (!CheckOperAndNum(str)) return err_ = "Missing operand";
//   if (!CheckBracer(str)) return err_ = "Empty parenthesis found";
//   if (!CheckBracerCount(str)) return err_ = "Missing parenthesis";
//   if (!CheckDotAndExp(str)) return err_ = "Extra dot or expander";

//   return err_;
// }

// void CalcModel::DelSpace(std::string& str) {
//   size_t i = 0;
//   int j = 0;
//   while (i < str.size()) {
//     if (str[i] == ' ') {
//       i++;
//     } else {
//       str[j] = str[i];
//       i++;
//       j++;
//     }
//   }
//   str[j] = 0;
// }

// bool CalcModel::CheckLenght(const std::string& str) {
//   if (str.size() <= max_size_) return true;
//   return false;
// }

// bool CalcModel::CheckSymvols(std::string str) {
//   int flag = 1;

//   while (flag != 0) {
//     flag = 0;
//     for (auto& q : tokens_) {
//       std::string::size_type pos = str.find(q);
//       if (pos != std::string::npos) {
//         str.erase(pos, q.length());
//         if (str.size() == 0) return true;
//         flag = 1;
//         break;
//       }
//     }
//   }

//   return false;
// }

// bool CalcModel::CheckNumber(const std::string& str) {
//   size_t i = 0;
//   while (i < str.size()) {
//     if (str[i] == 'x') return true;
//     if ((str[i] >= 48 && str[i] <= 57)) return true;
//     if (str[i] == 'p') {
//       i++;
//       if (str[i] == 'i') {
//         i++;
//         return true;
//       }
//     }
//     if (str[i] == 'i') {
//       i++;
//       if (str[i] == 'n') {
//         i++;
//         if (str[i] == 'f') {
//           i++;
//           return true;
//         }
//       }
//     }
//     i++;
//   }
//   return false;
// }

// bool CalcModel::CheckOperAndNum(const std::string& str) {
//   size_t i = 0;

//   if (str[i] == '-' || str[i] == '+' || str[i] == '(') {
//     i++;
//   }

//   for (; i < str.size(); i++) {
//     if ((str[0] == '^' || str[0] == '%' || str[0] == '/' || str[0] == '*'))
//       return false;

//     if ((str[i] == '^' || str[i] == '%' || str[i] == '/' || str[i] == '*') &&
//         (!IsPrefCharDigit(str[i - 1]) || !IsNextCharValid(str[i + 1])))
//       return false;

//     if ((str[i] == '-' || str[i] == '+') &&
//         (!IsPrefCharValid(str[i - 1]) || !IsNextCharValid(str[i + 1])))
//       return false;

//     if (str[i] == '(' && !IsPrevOperValue(str[i - 1])) return false;

//     if (str[i] == ')' && i != str.size() - 1 && !IsNextOperValue(str[i + 1]) &&
//         str[i + 1] != ')')
//       return false;
//   }

//   return true;
// }

// int CalcModel::CheckBracer(std::string& str) {
//   int status = 1;
//   size_t i = 0;

//   while (i < str.size() && status) {
//     if (str[i] == '(' && str[i + 1] == ')') status = 0;
//     i++;
//   }

//   return status;
// }

// int CalcModel::CheckBracerCount(std::string& str) {
//   int status = 1;
//   size_t i = 0;
//   int br_open = 0;
//   int br_close = 0;

//   while (i < str.size()) {
//     if (str[i] == '(') br_open++;
//     if (str[i] == ')') br_close++;
//     i++;
//   }

//   if (br_open != br_close) status = 0;

//   return status;
// }

// int CalcModel::CheckDotAndExp(std::string& str) {
//   int status = 1;
//   size_t i = 0;

//   while (i < str.size() && status) {
//     if ((str[i] >= 48 && str[i] <= 57)) {
//       int exp = 0;
//       int dot = 0;
//       while ((str[i] >= 48 && str[i] <= 57) || str[i] == '.' || str[i] == 'e') {
//         i++;
//         if (str[i] == 'e') {
//           if (str[i + 1] == 0) status = 0;
//           if (exp) status = 0;
//           exp = 1;
//         } else if (str[i] == '.') {
//           if (dot || exp) status = 0;
//           dot = 1;
//         }
//       }
//     }
//     if (str[i] == '.') {
//       if (i == 0)
//         status = 0;
//       else {
//         if (str[i - 1] < 48 || str[i - 1] > 57) status = 0;
//         if (str[i + 1] < 48 || str[i + 1] > 57) status = 0;
//       }
//     }
//     i++;
//   }
//   return status;
// }

// bool CalcModel::IsPrevOperValue(char i) {
//   if (IsNextOperValue(i) || i == '(' || i == 'n' || i == 'g' || i == 's' ||
//       i == 't')
//     return true;
//   return false;
// }

// bool CalcModel::IsNextOperValue(char i) {
//   if (i == '-' || i == '+' || i == '*' || i == '/' || i == '^' || i == '%')
//     return true;
//   return false;
// }

// bool CalcModel::IsPrefCharDigit(char i) {
//   if ((i >= 48 && i <= 57) || i == ')' || i == 'x' || i == 'f' || i == '.' ||
//       i == 'i')
//     return true;
//   return false;
// }

// bool CalcModel::IsNextCharValid(char i) {
//   if ((i >= 48 && i <= 57) || i == '(' || i == 'x' || i == 'i' || i == 'c' ||
//       i == 'l' || i == 'a' || i == 's' || i == 't' || i == 'p')
//     return true;
//   return false;
// }

// bool CalcModel::IsPrefCharValid(char i) {
//   if (IsPrefCharDigit(i) || i == '(' || i == 'e') return true;
//   return false;
// }

// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //================= CREDIT==============================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================
// //======================================================


// s21::CreditOptions& CalcModel::GetCreditResAnui(CreditOptions& crd) {
//   double i = crd.proc / 100 / 12;
//   crd.every_m = crd.summ * (i + (i / (pow(1 + i, crd.srok) - 1)));
//   crd.objaja = crd.srok * crd.every_m;
//   crd.pereplata = crd.objaja - crd.summ;
//   return crd;
// }

// s21::CreditOptions& CalcModel::GetCreditResDiff(CreditOptions& crd) {
//   crd.every_m = 0;
//   crd.every_m =
//       crd.summ / crd.srok +
//       (crd.summ - (crd.summ / crd.srok) * (crd.row)) * ((crd.proc / 100) / 12);
//   crd.objaja = crd.objaja + crd.every_m;
//   crd.pereplata = crd.objaja - crd.summ;
//   return crd;
// }

// void getCredResDiff(double summ, double proc, double srok, double* every_m,
//                     double* pereplata, double* objaja, int col) {
//   *every_m = 0;
//   *every_m = summ / srok + (summ - (summ / srok) * (col)) * ((proc / 100) / 12);
//   *objaja = *objaja + *every_m;
//   *pereplata = *objaja - summ;
// }

// bool CalcModel::IsTrigoChar(char c) {
//   if (c == 'c' || c == 'o' || c == 'x' ||
//       c == 'q' || c == 'r' || c == 't' ||
//       c == 'i' || c == 'n' || c == 'a' ||
//       c == 'l' || c == 'g' || c == 's'
//       ) return true;
//   return false;
// }

// std::string& CalcModel::GetError() { return err_; }

// void CalcModel::UpMaxSize() { max_size_ = max_size_ + 2; }

// void CalcModel::SetErrDefault() { err_ = "no_err"; }

// void CalcModel::SetAnsDefault() { answer_ = 0; }

// }  // namespace s21
