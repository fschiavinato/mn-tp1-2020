#pragma once
#include<iostream>
using namespace std;

#define forn(i,n) for(int i=0;i<int(n);i++)
#define dforn(i,n) for(int i=int(n)-1;i>=0;i--)
#define forsn(i,s,n) for(int i=int(s);i<int(n);i++)
#define dforsn(i,s,n) for(int i=int(n)-1;i>=int(s);i--)

#define debug(x) clog << __LINE__  << ") " << #x << " = " << x << endl
#define RAYA clog << "===============================" << endl