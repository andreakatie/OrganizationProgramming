     1  #include <iostream>
     2  #include <cmath>
     3
     4  using namespace std;
     5
     6  namespace PFArraySavitch
     7  {
     8
     9          // from book and as noted in class, this base class is used
    10          template<class T>
    11          class PFArray
    12          {
    13          public:
    14                  PFArray();
    15          private:
    16                  int usedB;
    17                  T *b;
    18          };
    19
    20          // #3, part 1 - YES, they syntax is correct
    21          // Note that this was also a Self-Test Question from p. 724, ST-13, with answer on p. 727
    22          template<class T>
    23          class TwoDimPFArrayBak : public PFArray< PFArray<T> >
    24          {
    25          public:
    26                  TwoDimPFArrayBak();
    27          };
    28
    29
    30          template<class T>
    31          PFArray<T>::PFArray( ) : usedB(0)
    32          {
    33                  b = new T[10];
    34          }
    35
    36          template<class T>
    37          TwoDimPFArrayBak<T>::TwoDimPFArrayBak() {};
    38  }
    39
    40
    41  namespace Quiz2Day2
    42  {
    43
    44          class PiggyBank
    45          {
    46          public:
    47                  PiggyBank( );
    48                  PiggyBank(int Penny, int Nickel, int Dime, int Quarter);
    49                  double get() const;
    50                  int withdraw(double amount);
    51                  void printBank();
    52                  PiggyBank operator +(const PiggyBank& pb2) const;
    53                  bool operator ==(const PiggyBank& pb2) const;
    54
    55          private:
    56                  int Penny;
    57                  int Nickel;
    58                  int Dime;
    59                  int Quarter;
    60          };
    61
    62          PiggyBank::PiggyBank( ) : Penny(0), Nickel(0), Dime(0), Quarter(0)
    63          {
    64                  cout << "Default initialization\n";
    65          }
    66
    67          PiggyBank::PiggyBank(int Penny, int Nickel, int Dime, int Quarter)
    68          {
    69                  this->Penny = Penny;
    70                  this->Nickel = Nickel;
    71                  this->Dime = Dime;
    72                  this->Quarter = Quarter;
    73          }
    74
    75          void PiggyBank::printBank()  // this is real useful for debug, so I added
    76          {
    77                  cout << "\nPiggyBank contains:\n";
    78                  cout << "\tQuarters=" << this->Quarter << endl;
    79                  cout << "\tDimes=" << this->Dime << endl;
    80                  cout << "\tNickels=" << this->Nickel << endl;
    81                  cout << "\tPennies=" << this->Penny << endl << endl;
    82          }
    83
    84          double PiggyBank::get() const
    85          {
    86                  return (((double)Penny * 0.01)+((double)Nickel * 0.05) + ((double)Dime * 0.10) + ((double)Quarter * 0.25));
    87          }
    88
    89          int PiggyBank::withdraw(double amount)
    90          {
    91                  double currentVal = this->get();
    92                  double adjustedVal;
    93
    94                  adjustedVal = currentVal - amount;
    95                  cout << "Current value=" << this->get() << ", withdrawal of " << amount << " leaves " << adjustedVal << endl;
    96
    97                  Quarter = (int) (adjustedVal / 0.25); // number of Quarters in bank after withdrawal
    98                  adjustedVal = adjustedVal - (Quarter * 0.25);
    99                  cout << "Quarters=" << Quarter << ", adjustedVal=" << adjustedVal << endl;
   100
   101                  Dime = (int) (adjustedVal / 0.10); // number of Dimes in bank after withdrawal
   102                  adjustedVal = adjustedVal - (Dime * 0.10);
   103                  cout << "Dimes=" << Dime << ", adjustedVal=" << adjustedVal << endl;
   104
   105                  Nickel = (int) (adjustedVal / 0.05); // number of Nickels in bank after withdrawal
   106                  adjustedVal = adjustedVal - (Nickel * 0.05);
   107                  cout << "Nickels=" << Nickel << ", adjustedVal=" << adjustedVal << endl;
   108
   109                  Penny = (int) (adjustedVal / 0.01); // number of Pennies in bank after withdrawal
   110                  adjustedVal = adjustedVal - (Penny *0.01);
   111                  cout << "Pennies=" << Penny << ", adjustedVal=" << adjustedVal << endl;
   112
   113                  return 0;
   114          }
   115
   116          bool PiggyBank::operator ==(const PiggyBank& pb2) const
   117          {
   118                  double pb2Val=pb2.get(), pb1Val=this->get();
   119
   120                  // same to the penny, any other difference is floating point error
   121                  return (abs(pb1Val - pb2Val) < 0.01);
   122          }
   123
   124          PiggyBank PiggyBank::operator +(const PiggyBank& pb2) const
   125          {
   126                  return PiggyBank((this->Penny + pb2.Penny), (this->Nickel + pb2.Nickel), (this->Dime + pb2.Dime), (this->Quarter + pb2.Quarter));
   127          }
   128  }
   129
   130
   131  // #3, part 2 version of swap for any type
   132  template<class T>
   133  void swapV(T& v1, T& v2)
   134  {
   135          T temp;
   136
   137          temp=v1;
   138          v1=v2;
   139          v2=temp;
   140  }
   141
   142
   143  using PFArraySavitch::PFArray;
   144  using PFArraySavitch::TwoDimPFArrayBak;
   145  using Quiz2Day2::PiggyBank;
   146
   147  int main(void)
   148  {
   149          int *p1, *p2;
   150          p1 = new int;
   151          p2 = new int;
   152
   153          *p1 = 10;
   154          *p2 = 20;
   155
   156          cout << *p1 << " " << *p2 << endl;
   157          p1 = p2;
   158          cout << *p1 << " " << *p2 << endl;
   159          *p1 = 30;
   160          cout << *p1 << " " << *p2 << endl;
   161
   162          PFArray<int> testPFArrayObj;
   163          TwoDimPFArrayBak<int> testTwoDimPFArrayBakObj;
   164
   165          // Example of calls to template for swap as found on page 697
   166      int v1=1, v2=2;
   167          double dv1=1.0, dv2=2.0;
   168          char keyinput;
   169
   170          cout << "Original: v1=" << v1 << ", v2=" << v2 << endl;
   171          swapV(v1, v2);
   172          cout << "Swapped: v1=" << v1 << ", v2=" << v2 << endl;
   173
   174          cout << "Original: dv1=" << dv1 << ", dv2=" << dv2 << endl;
   175          swapV(dv1, dv2);
   176          cout << "Swapped: dv1=" << v1 << ", dv2=" << v2 << endl;
   177
   178          // #7 part 1 and 2
   179          PiggyBank myBankObj(15, 10, 15, 11);
   180
   181          myBankObj.printBank();
   182
   183          cout << "Piggy bank balance= " << myBankObj.get() << endl;
   184          myBankObj.withdraw(2.37);
   185          cout << "Piggy bank balance= " << myBankObj.get() << endl;
   186
   187          myBankObj.printBank();
   188
   189          // #8
   190          PiggyBank myBank(15, 10, 15, 11);
   191          PiggyBank yourBank(5, 12, 10, 13);
   192          PiggyBank ourBank;
   193
   194          cout << "My bank balance= " << myBank.get() << endl;
   195          cout << "Your bank balance= " << yourBank.get() << endl;
   196
   197
   198          if(myBank == yourBank)
   199                  cout << "Both banks are of equal value\n";
   200
   201          ourBank = yourBank + myBank;
   202          cout << "Combined bank balance= " << ourBank.get() << endl;
   203
   204          cout << "Press any key and return to terminate\n";
   205          cin >> keyinput;
   206
   207          return 0;
   208  }
