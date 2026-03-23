#include<vector>
#include<algorithm>
void sort_even(std::vector<int>& arr)  {
  int even = 0; int odd = arr.size() - 1;
  while (even < odd) {
    if (arr[even] % 2 == 0) {
      even++;
    } else {
      std::swap(arr[even], arr[odd]);
      odd--;
    }
  }
}

void print_vec(std::string preamble, std::vector<int> arr) {
  printf("%s", preamble.c_str());
  for (int x : arr) {
    printf("%d, ", x);
  }
  printf("\n");
}

int main() {
  std::vector<int> arr = {4,3,6,-1,3,8,9,7};
  print_vec("original: ", arr);
  sort_even(arr);
  print_vec("new: ", arr);
  return 0;
}
