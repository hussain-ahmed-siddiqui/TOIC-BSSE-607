#include<bits/stdc++.h>
#define LOWER_X -15 
#define UPPER_X +15 
#define LOWER_Y -25 
#define UPPER_Y +20 
using namespace std;


struct individual{
    float x;
    float y;
    float f;

    void evaluateFitness(){
        // f = (11*x)-(7.59*y);
        f = 100-pow((x-7*y),2)+8*pow(y,2)-6*x;
    }
};



//Adjust fitness by adding smallest fitness to each fitness plus 1 to get rid of negative fitness
vector<float> getAdjustedFitness(vector<individual> population){

    vector<float> new_fitness(10);

    float smallest=INT32_MAX;
    for(individual person: population){
        if(smallest > person.f) smallest = person.f;
        }
    smallest = abs(smallest);

    for(int i=0;i<10;i++){
        new_fitness[i] = population[i].f + smallest+1;
    }

    return new_fitness;
}

//calculation of probabilites of selection of individuals based on calculation of fitness proportion
void calculate_culmutative_proportions(vector<float> &adjustedFitness, vector<individual> &population,map<individual*, float> &culmutative){

vector<float> proportion(adjustedFitness.size());
float fitnessSum=0;
for( float fitness: adjustedFitness){
    fitnessSum += fitness;
}

for(int i=0;i<proportion.size();i++){
    proportion[i]=adjustedFitness[i]/fitnessSum;
}
    cout<<"\nProportions\n";
    for(float val: proportion){
        cout<<val<<"\n";
    }
    culmutative[&population[0]]=proportion[0];

    for(int i=1;i<10;i++){
        culmutative[&population[i]] = proportion[i]+culmutative[&population[i-1]];
    }
    cout<<"\nCulmutative\n";

    for(auto x:culmutative){
        cout<<"\n"<<x.second;
    }
cout<<"\n";
}

//Seed calculation
//******************************
// Get high-resolution time point
    auto now = chrono::high_resolution_clock::now();

    // Convert time point to a number
    auto time_count = now.time_since_epoch().count();

    // Get the thread ID
    auto thread_id = this_thread::get_id();

    // Hash the thread ID
    size_t thread_id_hash = hash<thread::id>{}(thread_id);

    // Combine the high-resolution time with the thread ID hash
    unsigned seed = static_cast<unsigned>(time_count) ^ static_cast<unsigned>(thread_id_hash);

    mt19937 gen(seed); // Seed the generator with current time

//******************************    


//select a random parent based on culmutative proportion
individual getParent(vector<individual> &population, map<individual*, float> &culmutative){
    uniform_real_distribution<> rand(0, 1); 
    

    float num = rand(gen);
    float num2=0;
    cout<<"\n";
    for(auto x:culmutative){
       
        if(num>num2 && num<=x.second){
            cout<<x.first->x<<" "<<x.first->y<<" "<<x.first->f<<" "<<num<<"\n";
            return *x.first;
        }
        num2=x.second;
    }
return population[0];
}

void evolution(vector<individual> &population,vector<individual> &new_population, map<individual*, float> &culmutative_probablities){

    individual parent1 = getParent(population,culmutative_probablities);
    individual parent2 = getParent(population,culmutative_probablities);
    while(parent1.f == parent2.f) {
        cout<<"same\n";
        parent2 = getParent(population,culmutative_probablities);}

}

int main(){

 #ifndef ONLINE_JUDGE

    freopen("v4_input.txt", "r", stdin);

    freopen("v4_output.txt", "w", stdout);

#endif
    ofstream fout(getenv("OUTPUT_PATH"));
    ios_base::sync_with_stdio(false);
    cin.tie(0);

vector<individual> population;//initial population
vector<individual> new_population;//for new population 
map<individual*, float> culmutative;//culmutative fitness proportions


float x,y;
int i=0;
//read from input file
for(individual person;i<10;i++)
{
    cin>>x>>y;
    person.x=x;
    person.y=y;
    person.evaluateFitness();
    population.push_back(person);
}

//print population
for(auto person:population){
    cout<<"X: "<<person.x<<" Y: "<<person.y<<" Fitness: "<<person.f<<"\n";
}

vector<float> new_fitness=getAdjustedFitness(population);

cout<<"\nAfter Adjusting fitness: \n";

//print adjusted fitness of population
for(float fitness :new_fitness){
    cout<<fitness<<"\n";
}

//calculate F.P and C.F.P
calculate_culmutative_proportions(new_fitness,population,culmutative);

//testing of parent selection
evolution(population,new_population,culmutative);

    cout<<flush;

return 0;
}