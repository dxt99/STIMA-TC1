#include<bits/stdc++.h>
#include<unistd.h>
#include<chrono>
#define pb push_back
#define underline "\033[4m"
#define DEFAULT "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
using namespace std;
using namespace std::chrono;

// 8 search directions
int dx[8]={0,0,1,1,1,-1,-1,-1};
int dy[8]={1,-1,0,1,-1,0,1,-1};

// Puzzle
vector<char> arr[100];
int col[100][100]; //determines color for output

// Words
vector<string> s;

// Answers
struct info{
	int x;
	int y;
	int dir; //direction
	int l; //length
};

vector<info> ans;

// Sizes
int n,m=0; //array size
int k=0; //words size

// Functions
bool inside(int x,int y){
	return (x>=0&&y>=0)&&(x<n&&y<m);
}

// Main
int main(){
	// time and comparison counter
	int cnt=0;
	// input
	string filename;
	cout<<"Masukkan nama file: ";
	cin>>filename;
	filename="../test/"+filename+".txt";
	ifstream in;
	in.open(filename);
	if(!in){
		cout<<"File tidak ditemukan!"<<endl;
		return 0;
	}
	int t=0; // puzzle idx
	string temp;
	while(getline(in,temp)){
		if(temp.size()==0)continue;
		if(temp[1]==' '||temp[1]=='\n'){
			for(int i=0;i<temp.size();i+=2)arr[t].pb(temp[i]);
			t++;
		}else{
			s.pb(temp);
		}
	}
	n=t;
	m=arr[0].size();
	k=s.size();
	
	// search
	auto start = high_resolution_clock::now();
	for(int i=0;i<n;i++){ //iterate over coordinates
		for(int j=0;j<m;j++){
			for(auto word:s){ //iterate over words
				for(int d=0;d<8;d++){ //iterate over directions
					int idx=0;
					int x=i;
					int y=j;
					while(inside(x,y)&&idx<word.size()&&word[idx]==arr[x][y]){
						cnt++;
						x+=dx[d];
						y+=dy[d];
						idx++;
						while(word[idx]==' ')idx++;
					}
					if(idx==word.size()){ //ans found
						info temp={i,j,d,idx};
						ans.pb(temp);
					}
				}
			}
		}
	}
	
	// output answer
	if(ans.size()==0){
		cout<<"Tidak ada solusi yang ditemukan!"<<endl;
		return 0;
	}
	int curcol=1;
	for(auto i:ans){
		while(i.l--){ //set color
			col[i.x][i.y]=curcol;
			i.x+=dx[i.dir];
			i.y+=dy[i.dir];
		}
		curcol++;
		if(curcol>6)curcol-=6;
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){ //print everything
			switch(col[i][j]){
				case 1:
					printf("%s%s%c%s ",underline,RED,arr[i][j],DEFAULT);
					break;
				case 2:
					printf("%s%s%c%s ",underline,GREEN,arr[i][j],DEFAULT);
					break;
				case 3:
					printf("%s%s%c%s ",underline,YELLOW,arr[i][j],DEFAULT);
					break;
				case 4:
					printf("%s%s%c%s ",underline,BLUE,arr[i][j],DEFAULT);
					break;
				case 5:
					printf("%s%s%c%s ",underline,MAGENTA,arr[i][j],DEFAULT);
					break;
				case 6:
					printf("%s%s%c%s ",underline,CYAN,arr[i][j],DEFAULT);
					break;
				default:
					printf("%c ",arr[i][j]);
			}
		}
		printf("\n");
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout<<endl;
	cout<<"Waktu eksekusi program: "<< duration.count()<<" mikrosekon"<<endl;
	cout<<"Banyak perbandingan yang dilakukan: "<<cnt<<" perbandingan"<<endl;
	cout<<"Banyak kata yang ditemukan: "<<ans.size()<<"/"<<k<<endl;
	
	return 0;
}
