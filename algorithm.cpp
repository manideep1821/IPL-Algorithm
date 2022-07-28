#include <bits/stdc++.h>
using namespace std;

// team deatils
class Team_Details {
    public :
    string teamname; 
    int total_matches;
    int won_matches;
    int lost_matches;
    int tie_matches;
    int total_points;
    double probability;
    int count_wins;
    float Nrr;
    
    void Set_Team_Details(string s , int w , int x , int y , int z , float r , int c = 0) {
        teamname = s;
        total_matches = w;
        won_matches = x;
        lost_matches = y;
        tie_matches = z;
        total_points = x * 2 + z;
        count_wins = 0;
        Nrr = r;
    }
    
};

bool compare (pair <string , pair <int , float>> &p1 , pair <string , pair <int , float>> &p2) {
    if(p1.second.first == p2.second.first) return (p1.second.second > p2.second.second);
    else return (p1.second.first > p2.second.first);
}


int main() {
    
    // input the team deatils
    Team_Details teams[10];
    
    unordered_map<string, int>mp;
    for(int i = 0; i < 10; i++) {
        string s;
        int w , x , y , z;
        float r;
        cin >> s >> w >> x >> y >> z >> r;
        mp[s] = i;
        teams[i].Set_Team_Details(s , w , x , y , z , r);
    }
    
    
    // remaining matches .. 
    
    int rem_matches = 0;
    
    for(int i = 0; i < 10; i++) {
        rem_matches += (14 - teams[i].total_matches);
    }
    
    // checking 2 power remaining_matches
    
    // taking input of the remaining matches;
    
    rem_matches = rem_matches / 2;
    vector <pair <string , string> > remaining_matches(rem_matches);
    
    for(int i = 0; i < rem_matches; i++) {
        string first_team , second_team;
        cin >> first_team >> second_team;
        remaining_matches[i].first = first_team;
        remaining_matches[i].second = second_team;
    }   
    
    
    // total_chances = 2 power (rem_matches);
    
    int total_chances = 1 << (rem_matches);
    
    cout << "remaining matches : " << rem_matches << "\n";
    
    for(int mask = 0; mask < total_chances; mask++) {
        
        //storing total points from the combinations
        unordered_map<string, int>points; 
        
        vector <pair<string , pair <int , float>>> store(10);
        
        for(int i = 0; i < 10; i++) {
            points[teams[i].teamname] = teams[i].total_points;
        }
        
        for(int i = 0; i < rem_matches; i++) {
            if((1 << i) & mask) {
                points[remaining_matches[i].second] += 2;
            }
            else {
                points[remaining_matches[i].first] += 2;
            }
        }
        
        // sorting based on total points and nrr
        for(int i = 0; i < 10; i++) {
            store[i].first = teams[i].teamname;
            store[i].second.first = points[teams[i].teamname];
            store[i].second.second = teams[i].Nrr;
        }
        
        sort(store.begin() , store.end() , compare);
        
        // taking the top4 teams to playoffs
        
        for(int i = 0; i < 4; i++) {
            teams[mp[store[i].first]].count_wins++;
        }
    }
    
    for(int i = 0; i < 10; i++) {
        teams[i].probability = (teams[i].count_wins * 100) / (float) (total_chances);
    }
    
    for(int i = 0; i < 10; i++) {
        cout << teams[i].teamname << " " << teams[i].probability <<  " " << "\n";
    }
}