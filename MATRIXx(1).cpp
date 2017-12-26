
#include <iostream>
#include <stdexcept>
#include <map>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <cmath>
using namespace std;

class matrix
{
int **m_array;
int m,n; //m-строки, n-столбцы

public:
friend matrix operator*(matrix A,matrix B);
friend matrix operator+ (matrix A,matrix B);
friend matrix operator*(matrix A,double x);
friend ostream &operator<<(ostream &stream,matrix C);
friend double determine(matrix A);
friend matrix tran(matrix A);
matrix& operator=(matrix I)//перегрузка
{
  m_array = new int* [I.m];
  for (int count = 0; count < I.m; count++)
  m_array[count] = new int [I.n];
  m=I.m; n=I.n;
   for (int i = 0; i < m; i++)
    {for (int j = 0; j < n; j++)
             {m_array[i][j] = I.m_array[i][j];}}
  return *this;
}
matrix(int k,int p)
{
m_array = new int* [k];
for (int count = 0; count < k; count++)
m_array[count] = new int [p];
m=k; n=p;

}

double determ(int** Arr, int size)
{
        int i,j;
        double det=0;
        int** matr;
        if(size==1)
        {
                det=Arr[0][0];
        }
        else if(size==2)
        {
                det=Arr[0][0]*Arr[1][1]-Arr[0][1]*Arr[1][0];
        }
        else
        {
                matr=new int*[size-1];
                for(i=0;i<size;++i)
                {
                        for(j=0;j<size-1;++j)
                        {
                                if(j<i)
                                        matr[j]=Arr[j];
                                else
                                        matr[j]=Arr[j+1];
                        }
                        det+=pow((double)-1, (i+j))*determ(matr, size-1)*Arr[i][size-1];
                }
                delete[] matr;
        }
        return det;
}
void fill_matrix()
{ char a[6];
int u=0;
int h;
int i=-1;
while (i<m-1)
{ i++;
cout<<"Введите элементы "<<i+1<<" строки:"<<endl;
for (int j=0;j<n;j++)
{ h=1;u=0;
    cin>>a;
     for (int k=0;k<=strlen(a)-1;k++)
    {if (((int)a[k]>=48)&&((int)a[k]<=57))
{
    u=u*10+(int)a[k]-48;}
else {if (j==0)
    {
        i=i-1;j=n;cout<<"ошибка ввода"<<endl;break;
    }
    else

    {j=j-1;cout<<"ошибка ввода"<<endl;break;}}
    m_array[i][j]=u;
    }
}
}

}
double determine()
{
    if (n==m) {
int size=n;
return determ(m_array,size);}
else {cout<<"Ошибка.Матрица не квадратная!"<<endl;return 0; }
}
matrix tran()
{int i,j;
int s;
matrix C(m,n);
for(i=0; i < m; i++)
 for(j=0; j < n; j++)
 {
    C.m_array[i][j]=m_array[i][j];
 }
for(i=0; i < m; i++)
 for(j=i+1; j < n; j++){
 s=C.m_array[i][j];
 C.m_array[i][j]=C.m_array[j][i];
 C.m_array[j][i]=s;}

 return C;
}



};


matrix operator+(matrix A,matrix B)
{
matrix C(A.m,A.n);
if ((A.m==B.m)&&(A.n==B.n))
{for (int i=0;i<A.m;i++)
{
for (int j=0;j<B.n;j++)
{
C.m_array[i][j]=A.m_array[i][j]+B.m_array[i][j];
}}}
else {cout<<"Oшибка.Матрицы разного размера!"<<endl;return C;}
return C;
}




void show_all_matrix(map<char,matrix> all_matrix)
{
    map<char,matrix>::iterator it = all_matrix.begin() ;
    for (  it = all_matrix.begin(); it != all_matrix.end(); ++it)///вывод на экран
  {
     cout << it->first << " : \n"<< it->second << endl;
  }

}




matrix operator*(matrix A,matrix B)
{
matrix C(A.m,B.n);

if (A.n==B.m) {
for (int i=0;i<A.m;i++)
{
for (int j=0;j<B.n;j++)
{
C.m_array[i][j]=0;
for (int k=0;k<A.n;k++)
{
C.m_array[i][j]+=A.m_array[i][k]*B.m_array[k][j];
}

}

}
return C;}
cout<<"Ошибка.Не выполняется условие перемножение матриц!"<<endl;
return B;
}
matrix operator*(matrix A,double x)
{
   for (int i=0;i<A.m;i++)
    {
       for (int j=0;j<A.n;j++)
       {
           A.m_array[i][j]*=x;
       }
    }
    return A;
}
ostream &operator<<(ostream &stream,matrix C)
{

for (int i=0;i<C.m;i++)
{
for (int j=0;j<C.n;j++)
{
printf("%4d ",C.m_array[i][j]);
}
printf("\n");
}
return stream;
}

int main()
{
setlocale(LC_ALL, "Russian");
char i[255];

int m,n,q;
char name;

map <char,matrix> all_matrix;
matrix L(2,2);
while(atoi(i)!=8)
{

cout<<"Выберите операцию:  1-транспонирование, 2-определитель"<<endl<<"3-умножение на число, 4-сложить матрицы, 5-перемножить матрицы, 6-добавить матрицу, 7-показать все матрицы, 8-выход"<<endl;
cin>>i;


cout<<endl;
switch(atoi(i)){
case 1 :
   { char a;
cin>>a;
     try{L=all_matrix.at(a).tran();
    all_matrix.erase('L');
    all_matrix.insert ( pair<char,matrix>('L',L) );
    cout<<L;
    }
    catch (const out_of_range& oor) {
    cerr << "Oшибка ввода. Возмоно такой матрицы нет :(" << '\n';
  }



     break;
   }
 case 2:{
     q=0;
    char a;
    cin>>a;
    try{cout<<all_matrix.at(a).determine()<<endl;

    }
    catch (const out_of_range& oor) {
    cerr << "Oшибка ввода. Возмоно такой матрицы нет :(" << '\n';
  }

break;
}
case 3:{
    cout<<"Выберите матрицу: ";
    char a;
    cin>>a;
    cout<<"Введите число: ";
    double x;
    cin>>x;
    try{L=all_matrix.at(a)*x;
    all_matrix.erase('L');
    all_matrix.insert ( pair<char,matrix>('L',L) );
    cout<<L;
    }
    catch (const out_of_range& oor) {
    cerr << "Oшибка ввода. Возмоно такой матрицы нет :(" << '\n';
  }
    break;
}

case 4:{
    cout<<"Выберите матрицы: ";
    char a,b;
    cin>>a;
    cin>>b;
    try{L=all_matrix.at(a)+all_matrix.at(b);
    all_matrix.erase('L');
    all_matrix.insert ( pair<char,matrix>('L',L) );
    cout<<L;
    }
    catch (const out_of_range& oor) {
    cerr << "Oшибка ввода. Возмоно такой матрицы нет :(" << '\n';
  }
    break;
}


case 5:{
    cout<<"Выберите матрицы: ";
    char a,b;
    cin>>a;
    cin>>b;
    try{L=all_matrix.at(a)*all_matrix.at(b);
    all_matrix.erase('L');
    all_matrix.insert ( pair<char,matrix>('L',L) );
    cout<<L;
    }
    catch (const out_of_range& oor) {
    cerr << "Oшибка ввода. Возмоно такой матрицы нет :(" << '\n';

  }break;}
case 6:
    {
     q=0;
     cout<<"Введите литеру матрицы: ";
     cin>>name;
     while (q==0) if ((int)name==76) {cout<<"это название использовать нельзя"<<endl;cin>>name;} else {q=1;}
     try
     {
         cout<<all_matrix.at(name)<<endl;
         cout<<"Такая матрица уже есть. Переписать?  <Y/N> "<<endl;
         char ans[255];
         cin>>ans;
         if(ans[0]=='Y')
            {
                cout<<"Заполним матрицу "<<name<<": "<<endl;
                cout<<"Количество строк: ";
                cin>>m;
                cout<<"Количество столбцов: ";
                cin>>n;
                matrix A(m,n);
                A.fill_matrix();
                all_matrix.at(name)=A;
            }
         else if(ans[0]=='N') {break;}
         else {cout<<"Ошибка"<<endl;break;}


    }
    catch (const out_of_range& oor)
    {
      cout<<"Заполним матрицу "<<name<<": "<<endl;
      cout<<"Количество строк: ";
      cin>>m;
      cout<<"Количество столбцов: ";
      cin>>n;
      matrix A(m,n);
      A.fill_matrix();
      all_matrix.insert ( pair<char,matrix>(name,A) );
    }
     break;
     }
case 7:
    {
      show_all_matrix(all_matrix);
      break;
    }
case 8:{cout<<"До свидания.";break;}
default: {cout<<"Ошибка ввода. Попробуйте ещё раз "<<endl;break;}
}
}


}
