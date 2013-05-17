#include <iostream>
#include <vector>
using namespace std;

class vec {

public:
  vec() {}
  vec(int elm, int val):vect(elm, val) {}
  int insert_vec(int num);
  int delete_vec(int num);
  int find_vec(int num);
  int size_vec();
  ~vec() {}

private:
  vector<int> vect;
};

int vec::insert_vec(int num) 
{
  vect.push_back(num);

  return 0;
}

int vec::delete_vec(int num)
{
  if (vect.empty()) {
    cout << "empty" << endl;
    return -1;
  }
  vector<int>::iterator iter;
  for(iter = vect.begin(); iter != vect.end(); iter++)
  {
    if (*iter == num) {
      // return the next element, so the step is 
      // 1. erase, 2. iter++, total add 2 times.
      // so need iter --
      vect.erase(iter);
      //iter --;
    }
  }

  return vect.size();
}

int vec::find_vec(int num) 
{
  if (vect.empty()) {
    cout << "empty" << endl;
    return -1;
  }
  for(int i = 0; i < vect.size(); i++)
  {
    if (vect[i] == num) {
      return vect[i];
    }
  }
  return -1;
}

int vec::size_vec() 
{
  if (vect.empty()) {
    cout << "empty" << endl;
    return 0;
  } else {
    return vect.size();
  }
}

int main(void)
{
  vec vecc;
  for (int i = 0; i < 10; i++)
  {
    vecc.insert_vec(i);
  }

  cout << "the size is "<< vecc.size_vec() << endl;
  cout << vecc.find_vec(3) << endl;
  vecc.delete_vec(8);
  cout << "the size is " << vecc.size_vec() << endl;

  vec vecc2(10, 5);
  cout << "the 2 size is "<< vecc2.size_vec() << endl;
  cout << vecc2.find_vec(3) << endl;
  // why the rest size is 5?
  cout << "the rest is " << vecc2.delete_vec(5) << endl;
  cout << "the 2 size is " << vecc2.size_vec() << endl;

  return 0;
}
