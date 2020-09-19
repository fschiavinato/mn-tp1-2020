#pragma once
#include<iostream>
#include"tipos/vector.h"
using namespace std;

#define etype long double
#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define debug(x) clog << __LINE__  << ") " << #x << " = " << x << endl
#define RAYA clog << "===============================" << endl