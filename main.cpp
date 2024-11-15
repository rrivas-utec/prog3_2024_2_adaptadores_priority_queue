#include <iostream>
#include <queue>
#include <stack>
#include <functional>

template<typename Type, typename ...OtherTypes>
struct is_same_to_any {
  constexpr static bool value = (std::is_same_v<Type, OtherTypes> || ...);
};
template<typename Type, typename ...OtherTypes>
constexpr bool is_same_to_any_v = is_same_to_any<Type, OtherTypes...>::value;
template<typename Type, typename ...OtherTypes>
struct is_same_to_all {
  constexpr static bool value = (std::is_same_v<Type, OtherTypes> && ...);
};
template<typename Type, typename ...OtherTypes>
constexpr bool is_same_to_all_v = is_same_to_all<Type, OtherTypes...>::value;

template <typename AdapterType, typename T = typename AdapterType::value_type, typename ContainerT = typename AdapterType::container_type>
void print_adapter(AdapterType adapter) {
  while (!adapter.empty()) {
    if constexpr (is_same_to_any_v<AdapterType, std::queue<T, ContainerT>> == true) {
      std::cout << adapter.front() << " ";
    }
    else if constexpr (is_same_to_any_v<AdapterType, std::stack<T, ContainerT>, std::priority_queue<T, ContainerT, typename AdapterType::value_compare>> == true){
      std::cout << adapter.top() << " ";
    }
    adapter.pop();
  }
  std::cout << std::endl;
}


void ejemplo_less() {
  std::less<int> less_enteros_1;
  std::less<> less_generic;
  
  int a = 10;
  int b = 20;
  int c = 5;
  
  std::cout << std::boolalpha << less_enteros_1(a, b) << std::endl;
  std::cout << std::boolalpha << less_generic(b, c) << std::endl;
  
  std::string t1 = "Ana";
  std::string t2 = "Sara";
  std::string t3 = "Analogia";
  
  std::cout << std::boolalpha << less_generic(t1, t2) << std::endl;
  std::cout << std::boolalpha << less_generic(t3, t1) << std::endl;
}

namespace utec {
  template<typename T = void>
  struct less {
    bool operator() (T a, T b) const {return a < b; }
  };
  template<>
  struct less<void> {
    template <typename U>
    bool operator() (U a, U b) const {return a < b; }
  };
}

void ejemplo_less_2() {
  utec::less<int> less_enteros_1;
  utec::less<> less_generic;
  
  int a = 10;
  int b = 20;
  int c = 5;
  
  std::cout << std::boolalpha << less_enteros_1(a, b) << std::endl;
  std::cout << std::boolalpha << less_generic(b, c) << std::endl;
  
  std::string t1 = "Ana";
  std::string t2 = "Sara";
  std::string t3 = "Analogia";
  
  std::cout << std::boolalpha << less_generic(t1, t2) << std::endl;
  std::cout << std::boolalpha << less_generic(t3, t1) << std::endl;
}

void ejemplo_pq_1() {
  std::priority_queue<int> q;
  q.push(10);
  q.push(20);
  q.push(15);
  q.push(6);
  q.push(8);
  print_adapter(q);
}

void ejemplo_pq_2() {
  std::vector v1 = {10, 20, 15, 6, 8};
  std::priority_queue<int> q(v1.begin(), v1.end());
  print_adapter(q);
}

void ejemplo_pq_3() {
  std::vector v1 = {10, 20, 15, 6, 8};
  std::priority_queue<int, std::vector<int>, std::greater<>> q(v1.begin(), v1.end());
  print_adapter(q);
}

struct Student {
  int code{};
  std::string name{};
  friend std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "(" << s.code << " " << s.name << ")";
    return out;
  }
};

bool operator>(const Student& a, const Student& b) {  // equivalente a std::greater
  return a.name > b.name;
}
bool operator<(const Student& a, const Student& b) {  // equivalente a std::less
  return a.name < b.name;
}

void ejemplo_pq_4() {
  Student s1{1, "Jose"};
  std::cout << s1 << std::endl;
}

void ejemplo_pq_5() {
  std::priority_queue<Student> q1;
  q1.emplace(1, "Jose");
  q1.emplace(2, "Maria");
  q1.emplace(3, "Jesus");
  print_adapter(q1);
}

void ejemplo_pq_6() {
  // Lambdas de Comparaciones
  auto compare_by_name_lmb_greater = [](auto a, auto b) { return a.name > b.name; };
  auto compare_by_code_lmb_greater = [](auto a, auto b) { return a.code > b.code; };
  
  std::vector<Student> vec_students = { {2, "Maria"}, {1, "Jose"}, {3, "Jesus"}};
  std::priority_queue<Student, std::vector<Student>, decltype(compare_by_code_lmb_greater)> q1(compare_by_code_lmb_greater, vec_students);
  print_adapter(q1);
  std::priority_queue<Student, std::vector<Student>, decltype(compare_by_name_lmb_greater)> q2(compare_by_name_lmb_greater, vec_students);
  print_adapter(q2);
}

void ejemplo_pq_7() {
  // Lambdas de Comparaciones
  auto compare_by_name_lmb_greater = [](auto a, auto b) { return a.name > b.name; };
  auto compare_by_code_lmb_greater = [](auto a, auto b) { return a.code > b.code; };
  
  std::vector<Student> vec_students = { {2, "Maria"}, {1, "Jose"}, {3, "Jesus"}};
  std::priority_queue<Student, std::vector<Student>, bool(*)(Student, Student)> q1(compare_by_code_lmb_greater, vec_students);
  print_adapter(q1);
  std::priority_queue<Student, std::vector<Student>, std::function<bool(Student, Student)>> q2(compare_by_name_lmb_greater, vec_students);
  print_adapter(q2);
}

int main() {
//  ejemplo_less();
//  ejemplo_less_2();
//  ejemplo_pq_1();
//  ejemplo_pq_2();
//  ejemplo_pq_3();
//  ejemplo_pq_4();
//  ejemplo_pq_5();
//  ejemplo_pq_6();
  ejemplo_pq_7();
  return 0;
}
