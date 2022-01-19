#include<bits/stdc++.h>
#include<unistd.h>
#define pb push_back
#define GREEN "\x1B[32m"
#define underline "\033[4m"
#define DEFAULT "\x1B[0m"
using namespace std;

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
	// input
	string filename;
	cout<<"Masukkan nama file: ";
	cin>>filename;
	filename="test/"+filename+".txt";
	ifstream in;
	in.open(filename);
	if(!in){
		cout<<"File tidak ditemukan!"<<endl;
		return 0;
	}
	int t=0; // puzzle idx
	string temp;
	while(getline(in,temp)){
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
	for(int i=0;i<n;i++){ //iterate over coordinates
		for(int j=0;j<m;j++){
			for(auto word:s){ //iterate over words
				for(int d=0;d<8;d++){ //iterate over directions
					int idx=0;
					int x=i;
					int y=j;
					while(inside(x,y)&&idx<word.size()&&word[idx]==arr[x][y]){
						x+=dx[d];
						y+=dy[d];
						idx++;
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
	for(auto i:ans){
		while(i.l--){ //set color
			col[i.x][i.y]=1;
			i.x+=dx[i.dir];
			i.y+=dy[i.dir];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){ //print everything
			if(!col[i][j])printf("%c ",arr[i][j]);
			else printf("%s%c%s ",underline,arr[i][j],DEFAULT);
		}
		printf("\n");
	}
}
