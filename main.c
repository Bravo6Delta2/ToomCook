#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 1000
#define BASE 10000

int isZero (int* x){

    for (int i = 1; i<=abs(x[0]); i++){

        if(x[i] != 0)
            return 1;
    }
        return 0;
}

void import(int x[])
{
    printf("Enter number: ");

    int c, i = 0,j = 0;
    int znak = 1, y[4 * LENGTH];
    int q = 10;

    c = getchar();
    if (c == 45)
    {
        znak = -1;
        c = getchar();
    }

    while (c != 10)
    {
        y[i] = c - 48;
        i++;
        c = getchar();
    }


    c = y[i - 1];
    i = i - 2;

    while (i >= 0)
    {
        if (q < BASE)
        {
            c = c + y[i] * q;
            q = q * 10;
        }
        else
        {
            j++;
            x[j] = c;
            q = 10;
            c = y[i];
        }

        i--;
    }

    j++;
    x[j] = c;


    x[0] = znak * j;
}

void print_number(int x[])
{
    int i;
    int brGrupa = abs(x[0]);
    int p = BASE / 10;

    if (x[0] < 0)
    {
        printf("-");
    }

    printf("%d", x[brGrupa]);

    for (i = brGrupa - 1; i > 0; i--)
    {
        while (p > 0 && x[i] < p)
        {
            printf("0");
            p = p / 10;
        }

        if (x[i] != 0)
        {
            printf("%d", x[i]);
        }

        p = BASE / 10;
    }

    printf("\n");
}


void set0(int*a ,int n){
    for(int i=0;i<n;i++){
        a[i]=0;
    }
}

void aadd(int a[], int b[], int c[])
{
    // absolute addtion
    int prenos = 0, i;
    int a0 = abs(a[0]);
    int b0 = abs(b[0]);

    if (a0 > b0)
    {
        for(i = 1; i <= b0; i++)
        {
            c[i] = a[i] + b[i] + prenos;
            if (c[i] >= BASE)
            {
                prenos = 1;
                c[i] = c[i] - BASE;
            }
            else prenos = 0;
        }

        for (i = b0 + 1; i <= a0; i++)
        {
            c[i] = a[i] + prenos;
            if (c[i] >= BASE)
            {
                prenos = 1;
                c[i] = c[i] - BASE;
            }
            else prenos = 0;
        }

        if (prenos > 0)
        {
            c[a0 + 1] = prenos;
            c[0] = a0 + 1;
        }
        else c[0] = a0;
    }
    else
    {
        for(i = 1; i <= a0; i++)
        {
            c[i] = a[i] + b[i] + prenos;
            if (c[i] >= BASE)
            {
                prenos = 1;
                c[i] = c[i] - BASE;
            }
            else prenos = 0;
        }

        for (i = a0 + 1; i <= b0; i++)
        {
            c[i] = b[i] + prenos;
            if (c[i] >= BASE)
            {
                prenos = 1;
                c[i] = c[i] - BASE;
            }
            else prenos = 0;
        }

        if (prenos > 0)
        {
            c[b0 + 1] = prenos;
            c[0] = b0 + 1;
        }
        else c[0] = b0;
    }
}

void add(int x[], int y[], int z[]){

    int veci;
    if (x[0]*y[0]<0){
        veci=asub(x,y,z);
        if (((veci == 1) && (x[0]<0)) || ((veci==2) && (y[0]<0)))
            z[0]*=-1;
    }
    else {
        aadd(x,y,z);
        if (x[0] <0)
        {
            z[0]*=-1;
        }
    }

}


void multiplicate (int x[],int y[], int z[]){
    int x0, y0, z0, i, j, znak=1;

    x0=abs(x[0]);
    y0=abs(y[0]);

    if (x[0]*y[0]<0) znak=-1;

    for(i=1;i<=x0+y0;i++){
        z[i]=0;
    }

    for (i=1;i<=x0;i++){
        for (j=1;j<=y0;j++){
            z[i+j-1]+=x[i]*y[j];
            if (z[i+j-1] >= BASE){
                z[i+j] += z[i+j-1]/BASE;
                z[i+j-1] %= BASE;
            }
        }
    }

    z0=x0+y0;
    while ((z0>1) && (z[z0]==0)){
        z0--;
    }
    z[0]=z0*znak;
}
void multiplicate_const(int x[],int c,int z[]){
    int y[2];
    if(c<0){
        y[0]=-1;
    }else{
        y[0]=1;
    }

    y[1]=c;
    multiplicate(x,y,z);
}
void equalize(int x [], int y[]){
    int i;
    for(i=1; i<=abs(x[0]);i++){
        y[i]=x[i];
    }
    y[0]=x[0];
}

void divide_by_2(int x1[],int y[]){
    int x[LENGTH];
    equalize(x1,x);
    int i;
    for(i=1;i<abs(x[0]);i++){
        if(x[i+1]%2==1){
            x[i+1]--;
            y[i]=(BASE+x[i])/2;
        }else{
            y[i]=x[i]/2;
        }
    }

    y[abs(x[0])]=x[abs(x[0])]/2;

    if(y[abs(x[0])]==0){
        y[0]=abs(x[0])-1;
    }else{
        y[0]=abs(x[0]);
    }

    if(x[0]<0){
        y[0]*=-1;
    }
}

void divide_by_k(int a[],int konst,int z[]){
	int i,ostatak=0,temp;

	z[0]=a[0];

	for(i=abs(a[0]);i>=1;i--){
		temp=ostatak*BASE+a[i];
		ostatak=temp%konst;
		z[i]=temp/konst;
	}

	if(z[abs(z[0])]==0){
		if(z[0]<0) z[0]++;
		else z[0]--;
	}
}
int asub (int x[], int y[], int z[]){
    int x0,y0,i, pozajmica=0, veci=1;
    x0=abs(x[0]);
    y0=abs(y[0]);
    if (x0==y0){
        while ((x0>0) && (x[x0]==y[x0]))
            x0--;
        if (x0==0){
            veci=0;
            z[0]=1;
            z[1]=0;
        }
        else{
            if (x[x0] > y[x0]){

                for(i=1;i<=x0;i++){
                    z[i] = x[i]-y[i]-pozajmica;
                    if (z[i]<0){
                        pozajmica = 1;
                        z[i] += BASE;
                    }
                    else{
                        pozajmica = 0;
                    }
                }
                while (z[x0]==0){
                    x0--;
                }
                z[0]=x0;
            }
            else
            {
                veci=2;
                for(i=1;i<=x0;i++){
                    z[i] = y[i]-x[i]-pozajmica;
                    if (z[i]<0){
                        pozajmica = 1;
                        z[i] += BASE;
                    }
                    else{
                        pozajmica = 0;
                    }
                }
                while (z[x0]==0){
                    x0--;
                }
                z[0]=x0;
            }
        }
    }
    else{
        if (x0>y0){
            for(i=1;i<=y0;i++){
                z[i] = x[i]-y[i]-pozajmica;
                if (z[i]<0){
                    pozajmica = 1;
                    z[i] += BASE;
                }
                else{
                    pozajmica = 0;
                }
            }
            for(i=y0+1;i<=x0;i++){
                z[i] = x[i]-pozajmica;
                if (z[i]<0){
                    pozajmica = 1;
                    z[i] += BASE;
                }
                else{
                    pozajmica = 0;
                }
            }

            while (z[x0]==0){
                x0--;
            }
            z[0]=x0;

        }
        else{ //if (x0>y0)
            veci=2;
            for(i=1;i<=x0;i++){
                z[i] = y[i]-x[i]-pozajmica;
                if (z[i]<0){
                    pozajmica = 1;
                    z[i] += BASE;
                }
                else{
                    pozajmica = 0;
                }
            }
            for(i=x0+1;i<=y0;i++){
                z[i] = y[i]-pozajmica;
                if (z[i]<0){
                    pozajmica = 1;
                    z[i] += BASE;
                }
                else{
                    pozajmica = 0;
                }
            }

            while (z[y0]==0){
                y0--;
            }
            z[0]=y0;
        }

    }
    return veci;
}


void split(int x[],int p[3][LENGTH],int part_size){

    int i,j;

    int l=1;
    for(i=0;i<3;i++){
        if(l<=abs(x[0])){
            for(j=1;j<=part_size;j++){
                p[i][j]=x[l++];
                p[i][0]=j;
                if(l>abs(x[0])){
                    break;
                }
            }
        }else{

            p[i][0]=1;
            p[i][1]=0;
        }
    }

}

void shift (int* x,int k){

for (int i=0;i<k;i++){
        x[0]++;
    for(int j =x[0];j>i;j--){
        x[j]=x[j-1];
    }
    x[i+1]=0;
}

}

void remove0(int* z){

if(isZero(z) == 1){
while(z[z[0]] == 0){
    z[0]--;
}
}
else{

set0(z,LENGTH);
z[0] = 1;
}

}

void ToomCook_3(int* x,int* y,int* z){

    if (isZero(x)==0 || isZero(y)==0){

        z[0] =1;
        z[1] = 0;
        return;
    }

else if (abs(x[0]) < 4 || abs(y[0]) < 4){
    multiplicate(x,y,z);
    return;
}

int xx[3][LENGTH];
int yy[3] [LENGTH];

 int part_size=(abs(x[0])-1)/3+1;
 if((abs(y[0])-1)/3+1>part_size){
            part_size=(abs(y[0])-1)/3+1;
        }

split(x,xx,part_size);
split(y,yy,part_size);

for (int kkk = 0;kkk<3;kkk++){
    remove0(xx[kkk]);
    remove0(yy[kkk]);
}


int t0[5*LENGTH];

ToomCook_3(xx[0],yy[0],t0);

int tmp1[LENGTH];
int tmp2[LENGTH];


int p1[LENGTH];
int q1[LENGTH];

add(xx[2],xx[1],tmp1);
add(xx[0],tmp1,p1);

add(yy[2],yy[1],tmp2);
add(yy[0],tmp2,q1);


int t1[5*LENGTH];

ToomCook_3(p1,q1,t1);

set0(tmp1,LENGTH);
set0(tmp2,LENGTH);

int p_1[LENGTH];
int q_1[LENGTH];


xx[1][0] *= -1;

add(xx[2],xx[1],tmp1);

add(tmp1,xx[0],p_1);

xx[1][0] *= -1;

yy[1][0] *= -1;
add(yy[2],yy[1],tmp2);
add(tmp2,yy[0],q_1);
yy[1][0] *= -1;

int t2[5*LENGTH];

ToomCook_3(p_1,q_1,t2);

set0(tmp1,LENGTH);
set0(tmp2,LENGTH);

int temp3[LENGTH];
int temp4[LENGTH];
int temp5[LENGTH];
int temp6[LENGTH];

multiplicate_const(xx[2],4,temp3);
multiplicate_const(xx[1],2,temp4);
multiplicate_const(yy[2],4,temp5);
multiplicate_const(yy[1],2,temp6);


int p2[LENGTH];
int q2[LENGTH];

add(temp3,temp4,tmp1);
add(tmp1,xx[0],p2);

add(temp5,temp6,tmp2);
add(tmp2,yy[0],q2);


int t3[5*LENGTH];

ToomCook_3(p2,q2,t3);


set0(tmp1,LENGTH);
set0(tmp2,LENGTH);


int p_2 [LENGTH];
int q_2 [LENGTH];

temp4[0] *= -1;
add(temp3,temp4,tmp1);
add(tmp1,xx[0],p_2);
temp4[0] *= -1;

temp6[0] *= -1;
add(temp5,temp6,tmp2);
add(tmp2,yy[0],q_2);
temp6[0] *= -1;

int t4[5*LENGTH];

ToomCook_3(p_2,q_2,t4);

set0(tmp1,LENGTH);
set0(tmp2,LENGTH);
set0(temp3,LENGTH);
set0(temp4,LENGTH);
set0(temp5,LENGTH);
set0(temp6,LENGTH);

int temp7[LENGTH];
int d[LENGTH];
///(t4-t3-8*t2+8*t1)/12;

multiplicate_const(t1,8,tmp1);
multiplicate_const(t2,8,tmp2);

t3[0] *= -1;
add(t4,t3,temp3);
t3[0] *= -1;


tmp2[0] *= -1;
add(tmp1,tmp2,temp4);
tmp2[0] *= -1;
add(temp3,temp4,temp5);


divide_by_2(temp5,temp6);
divide_by_2(temp6,temp7);
divide_by_k(temp7,3,d);

int c[LENGTH];

set0(tmp1,LENGTH);
set0(tmp2,LENGTH);
set0(temp3,LENGTH);
set0(temp4,LENGTH);
set0(temp5,LENGTH);
set0(temp6,LENGTH);
set0(temp7,LENGTH);
/// ((t3  -4*t2   -12*t1   +15*t0) + 6*d)/12;

multiplicate_const(t2,4,tmp1);
multiplicate_const(t1,12,tmp2);
multiplicate_const(t0,15,temp3);
multiplicate_const(d,6,temp4);

add(tmp1,tmp2,temp5);
temp5[0]*=-1;
add(temp3,temp4,temp6);
add(temp5,temp6,temp7);

set0(tmp1,LENGTH);
add(temp7,t3,tmp1);

set0(temp5,LENGTH);set0(temp6,LENGTH);

divide_by_2(tmp1,temp5);
divide_by_2(temp5,temp6);
divide_by_k(temp6,3,c);


set0(tmp1,LENGTH);
set0(tmp2,LENGTH);
set0(temp3,LENGTH);
set0(temp4,LENGTH);
set0(temp5,LENGTH);
set0(temp6,LENGTH);
set0(temp7,LENGTH);


///((t2-t1) + 2*d)/2;
int b[LENGTH];

multiplicate_const(d,2,tmp1);
t1[0]*=-1;
add(t2,t1,tmp2);
t1[0]*=-1;
add(tmp1,tmp2,temp3);

divide_by_2(temp3,b);

///t1-t0-d+c+b;
set0(tmp1,LENGTH);
set0(tmp2,LENGTH);
set0(temp3,LENGTH);

int a[LENGTH];

t0[0]*=-1;
add(t1,t0,tmp1);
t0[0]*=-1;
add(c,b,tmp2);

add(tmp1,tmp2,temp3);
d[0]*= -1;
add(temp3,d,a);
d[0]*= -1;


set0(tmp1,LENGTH);
set0(tmp2,LENGTH);
set0(temp3,LENGTH);


if (t0[0] < 0 ){
    t0[0] *=-1;
}
if (d[0] < 0 ){
    d[0] *=-1;
}
if (c[0] < 0 ){
    c[0] *=-1;
}
if (b[0] < 0 ){
    b[0] *=-1;
}
if (a[0] < 0 ){
    a[0] *=-1;
}

shift(a,part_size*4);
shift(b,part_size*3);
shift(c,part_size*2);
shift(d,part_size);


add(t0,d,tmp1);
add(c,b,tmp2);
add(tmp1,tmp2,temp3);
add(temp3,a,z);

if(isZero(z) == 1){
while(z[z[0]] == 0){
    z[0]--;
}
}
else{

set0(z,LENGTH);
z[0] = 1;
}

if(x[0]*y[0]<1){
    z[0]*=-1;
}

}

int main()
{
    int a[LENGTH];
    int b[LENGTH];
    int c[10*LENGTH];

    import(a);
    import(b);

    ToomCook_3(a,b,c);
    printf("\n Res: \n");
    print_number(c);

    return 0;
}
