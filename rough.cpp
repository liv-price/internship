// Wormhole
#include <iostream>
#include <climits>
using namespace std;

int ANS = INT_MAX, n, temp = 0;
int w[35][5];
int mask[35];
 
int abs(int i)
{
    return (i >= 0) ? i : -1 * i;
}
 
int min(int x, int y)
{
    return (x >= y) ? y : x;
}
 
int dist(int sX, int sY, int tX, int tY)
{
    return abs(sX - tX) + abs(sY - tY);
}
 
void wormhole(int sX, int sY, int tX, int tY, int value)
{
    ANS = min(ANS, dist(sX, sY, tX, tY) + value);
 
    for (int i = 0; i < n; i++)
    {
        if (mask[i] == 0)
        {
            mask[i] = 1;
 
            /* Choose lower end of wormhole */
            temp = dist(sX, sY, w[i][0], w[i][1]) + w[i][4] + value;
            wormhole(w[i][2], w[i][3], tX, tY, temp);
 
            /* Choose upper end of wormhole */
            temp = dist(sX, sY, w[i][2], w[i][3]) + w[i][4] + value;
            wormhole(w[i][0], w[i][1], tX, tY, temp);
 
            mask[i] = 0;
        }
    }
}
 
int main()
{
    int t, sX, sY, tX, tY;
    cin >> t;
    while (t--)
    {
        ANS = INT_MAX;
        cin >> n;
        cin >> sX >> sY >> tX >> tY;
        for (int i = 0; i < n; i++)
        {
            mask[i] = 0;
            for (int j = 0; j < 5; j++)
            {
                cin >> w[i][j];
            }
        }
 
        wormhole(sX, sY, tX, tY, 0);
        cout << ANS << endl;
    }
    return 0;
}
 
// spaceship bomb
#include<iostream>
using namespace std;

void maxCoins(int arr[][5],int crow,int ccol,int temp,int &ans,int bomb,int effect){
	if(crow == -1){
		if(temp > ans){
			ans = temp;
		}
		return;
	}
	for(int i=-1;i<=1;i++){
		if((ccol+i) < 0 || (ccol+i) > 4)
			continue;
		if(arr[crow][ccol+i] == 1 || arr[crow][ccol+i] == 0){//No enemy
			if(bomb == 0){
				maxCoins(arr,crow-1,ccol+i,temp+arr[crow][ccol+i],ans,bomb,effect-1);//If bomb has already been used, reduce its effect by 1
			}else{
				maxCoins(arr,crow-1,ccol+i,temp+arr[crow][ccol+i],ans,bomb,effect);
			}
			
		}else{//Enemy
			if(bomb == 0){
				if(effect > 0){
					maxCoins(arr,crow-1,ccol+i,temp,ans,bomb,effect-1);//Bomb already used so can pass but effect reduces by 1
				}
			}else{
				maxCoins(arr,crow-1,ccol+i,temp,ans,0,5); //Use bomb ans set effect for five rows
			}
		}
	}
	return;
}

int main(){
	int arr[20][5],ans,t,n;
	cin>>t;
	for(int _=1;_<=t;_++) {
		cin>>n;
		for(int i=0;i<n;i++){
			for(int j=0;j<5;j++){
				cin >> arr[i][j];
			}
		}
	ans = 0;
	maxCoins(arr,n-1,2,0,ans,1,0);
	cout <<"#"<<_<<" "<< ans;
	}
	return 0;
}

//Kim and refigrator
#include <iostream>
#include <math.h>
using namespace std;

int n, sourceX = 0, sourceY = 0, destinationX = 100, destinationY = 100, shortestRoute;
int X[10], Y[10], visited[10];

int getDistance(int x1, int y1, int x2, int y2) {
    int x = x2 - x1;
    int y = y2 - y1;
    int result = abs(x) + abs(y);
    return result;
}

void explore(int current, int cost, int nodeLeft) {
    int i;
    if(nodeLeft <= 1) {
        if(cost + getDistance(X[current], Y[current], destinationX, destinationY) < shortestRoute)
            shortestRoute = cost + getDistance(X[current], Y[current], destinationX, destinationY);
        return;
    }
    // cout << current << ", " << cost << ", " << shortestRoute << endl;
    visited[current] = 1;
    for(i=0;i<n;i++) {
        if(visited[i] == 0)
            explore(i, cost + getDistance(X[current], Y[current], X[i], Y[i]), nodeLeft-1);
    }
    visited[current] = 0;
}

int main() {
    int i, t = 10;
    while (t--) {
        cin >> n;
        cin >> sourceX >> sourceY >> destinationX >> destinationY;
        for(i=0;i<n;i++) {
            cin >> X[i] >> Y[i];
            visited[i] = 0;
        }
        shortestRoute = 1000000;
        for(i=0;i<n;i++) {
            explore(i, getDistance(X[i], Y[i], sourceX, sourceY), n);
        }
        cout << "# " << (10-t) << " " << shortestRoute << endl;
    }
    return 0;
}

//burst ballon 
#include <iostream> 
using namespace std; 
  
// recursive function to generate scores 
int getmaxscore(int arr[], int l, int r, int n) 
{ 
    int mscore = 0; 
    for (int i = l + 1; i < r; i++) { 
  
        // to permute through all cases 
        int cs = getmaxscore(arr, l, i, n) + getmaxscore(arr, i, r, n); 
        if (l == 0 && r == n) 
            cs = cs + arr[i]; 
        else
            cs = cs + (arr[l] * arr[r]); 
  
        if (cs > mscore) 
            mscore = cs; 
    } 
    return mscore; 
} 
  
int main() // driver function 
{ 
    int n;
    cin>>n;
    int arr[15];  
      arr[0]=1 && arr[n+1]=1 
      cin>>n; 
      for(int i=1;i<=n;i++) 
         cin>>arr[i]; 
  
    cout << getmaxscore(arr, 0, n + 1, n + 1) << "\n"; 
  
    return 0; 
} 
// mr lee least ariplane fare
#include<iostream>
#include<climits>
using namespace std;

int N, result;

void minCostMrLee(int **arr, bool *visited, int count, int cost, int src){
    // Base Case
    if(count == N-1){
    	/* Corner Case if no path exists from last city */
        if(arr[src][0] != 0)
        	result = min(result, cost + arr[src][0]);
        return;
    }
    
    // Main Case
    for(int i=0; i<N; i++){
        if(!visited[i] && arr[src][i] != 0){
            visited[i] = true;
            minCostMrLee(arr, visited, count + 1, cost + arr[src][i], i);
            visited[i] = false;
        }
    }
}

int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> N;
		int **arr = new int*[N];
		for(int i=0; i<N; i++){
			arr[i] = new int[N];
		}
        bool *visited = new bool[N];
		
        for(int i=0; i<N; i++){
            visited[i] = false;
			for(int j=0; j<N; j++){
				cin >> arr[i][j];
			}
		}
		
        result = INT_MAX;    
        
        visited[0] = true;
        
        minCostMrLee(arr, visited, 0, 0, 0);
        result != INT_MAX ? cout << result << "\n" : cout << "-1\n";
	}
	return 0;
}

//endoscopy

#include<iostream>
using namespace std;

struct Node{
    bool left, right, up, down;
};

struct Point{
    int x, y;  
};

int n, m, sX, sY, len;
int arr[1005][1005];
int vis[1005][1005], dis[1005][1005];

int result;
Node pipes[1005][1005];
Point queue[1000005];

bool isValid(int i, int j){
    return (i>=0 && i<n && j>=0 && j<m);
}

void bfs(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vis[i][j] = 0;
            dis[i][j] = 0;
        }
    }
    
    int front = 0, rear = 0; 
    
    dis[sX][sY] = 1;
    vis[sX][sY] = 1;
    
    if( arr[sX][sY] == 0 ){
        result = 0;
        return;
    }
    
    queue[rear].x = sX;
    queue[rear].y = sY;
    rear = (rear + 1) % 1000005;
    
    while(front != rear){
        int p = queue[front].x;
        int q = queue[front].y;
        front = (front + 1) % 1000005;
        
        if( 1 + dis[p][q] <= len ){
            
            /* Row Up */
            if( isValid(p-1, q) && vis[p-1][q] == 0 && pipes[p-1][q].down && pipes[p][q].up ){
                vis[p-1][q] = 1;
                dis[p-1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p-1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Row Down */
            if( isValid(p+1, q) && vis[p+1][q] == 0 && pipes[p+1][q].up && pipes[p][q].down ){
                vis[p+1][q] = 1;
                dis[p+1][q] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p+1;
                queue[rear].y = q;
                rear = (rear + 1) % 1000005;
            } 
            
            /* Column Left */
            if( isValid(p, q-1) && vis[p][q-1] == 0 && pipes[p][q-1].right && pipes[p][q].left ){
                vis[p][q-1] = 1;
                dis[p][q-1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q-1;
                rear = (rear + 1) % 1000005;
            }          

            /* Column Right */
            if( isValid(p, q+1) && vis[p][q+1] == 0 && pipes[p][q+1].left && pipes[p][q].right ){
                vis[p][q+1] = 1;
                dis[p][q+1] = 1 + dis[p][q];
                result++;
                
                queue[rear].x = p;
                queue[rear].y = q+1;
                rear = (rear + 1) % 1000005;
            }          
                        
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	//code
	int t;
	cin >> t;
	while(t--){
	    result = 1;
	    cin >> n >> m >> sX >> sY >> len;
	    
	    for(int i=0; i<n; i++){
	        for(int j=0; j<m; j++){
	            cin >> arr[i][j];
	            
	            if( arr[i][j] == 1 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            } 
	            else if( arr[i][j] == 2 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 3 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	            else if( arr[i][j] == 4 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;
	            }
	            else if( arr[i][j] == 5 ){
	                pipes[i][j].left = false;
	                pipes[i][j].right = true;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 6 ){
	                pipes[i][j].left = true;
                    pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = true;
	            }
	            else if( arr[i][j] == 7 ){
	                pipes[i][j].left = true;
	                pipes[i][j].right = false;
	                pipes[i][j].up = true;
	                pipes[i][j].down = false;	                
	            }
	            else{
	                pipes[i][j].left = false;
	                pipes[i][j].right = false;
	                pipes[i][j].up = false;
	                pipes[i][j].down = false;	                
	            }
	 
	        }
	    }
	    
	    bfs();
	    cout << result << "\n";
	}
	return 0;
}

//samsung reacearch

#include<iostream>
using namespace std;
int row,col;
int a[100][100],visited[100][100],loc[100][2];
int sol=999999;
bool issafe(int x,int y) {
	return (x>=0 && x<row && y>=0 && y<col && a[x][y]==1 && visited[x][y]==0);
}
bool research(int x,int y,int x1,int y1,int count) {
	if(x==x1 && y==y1) {
		visited[x][y]=1;
		if(sol>count) {
			sol=count;
		}
		return true;
	}
	if(issafe(x,y)) {
		visited[x][y]=1;
		if(research(x,y-1,x1,y1,count+1)==true) {
			return true;
		}
		if(research(x,y+1,x1,y1,count+1)==true) {
			return true;
		}
		if(research(x-1,y,x1,y1,count+1)==true) {
			return true;
		}
		if(research(x+1,y,x1,y1,count+1)==true) {
			return true;
		}
	}
	return false;
}
int main() {
	int t,index=1;
	cin>>t;
	while(t--) {
		cin>>row>>col;
		for(int i=0;i<row;i++) {
			for(int j=0;j<col;j++) {
				cin>>a[i][j];
				visited[i][j]=0;
			}
		}
		int rare;
		cin>>rare;
		for(int i=0;i<rare;i++) {
			cin>>loc[i][0]>>loc[i][1];
		}
		int longest=0,flag=0,long_index=0,maxdist[row*col];
		for(int i=0;i<row;i++) {
			for(int j=0;j<col;j++) {
				if(a[i][j]==1) {
					for(int k=0;k<rare;k++) {
						if(research(loc[k][0],loc[k][1],i,j,0)==true) {
							if(longest<sol) {
								longest=sol;
							}
							sol=INT_MAX;
						}
						else {
							flag=1;
							break;
						}
					//	memset(visited,0,sizeof(visited));
						for(int i=0;i<row;i++) {
							for(int j=0;j<col;j++) {
								visited[i][j]=0;
							}
						}
					}
					if(flag==0) {
						maxdist[long_index]=longest;
						long_index++;
					}
					else {
						flag=0;
					}
					longest=0;
				}
			}
		}
		int j=0;
		for(int i=1;i<long_index;i++) {
			if(maxdist[i]<maxdist[j]) {
				j=i;
			}
		}
		cout<<"#"<<index<<" "<<maxdist[j]<<endl;
		index++;
	}
	return 0;
}
