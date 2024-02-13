#include<bits/stdc++.h>
#define LOWER_X -15 //0.5
#define UPPER_X +20 //7.5
#define LOWER_Y -20 //-4
#define UPPER_Y +25 //2.85
using namespace std;


struct individual{
    float x;
    float y;
    float f;

    void evaluateFitness(){
        // f = (11*x)-(7.59*y);
        f = -7*pow(x,2)+3*x*sin(y)-786*y+989;
    }
};

struct CompareIndividual {
    bool operator()(const individual& a, const individual& b) {
        return a.f < b.f; // use < for max heap
    }
};

void compareGens(vector<individual> &old_gen, vector<individual> &next_gen){

    priority_queue<individual,vector<individual>,CompareIndividual> new_population;
    for(int i=0;i<old_gen.size();i++){
        new_population.push(old_gen[i]);
        new_population.push(next_gen[i]);
    }    
    for(int i=0;i<old_gen.size();i++,new_population.pop()){
        old_gen[i]=new_population.top();
    }
}


float calculateAverageFitness(const vector<individual>& population) {
    float total_fitness = 0;
    for (const auto& ind : population) {
        total_fitness += ind.f;
    }
    return total_fitness / population.size();
}

void initializePopulation(vector<individual>& population){
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
    uniform_real_distribution<> rand_X(LOWER_X, UPPER_X); // define the range for x
    uniform_real_distribution<> rand_Y(LOWER_Y, UPPER_Y); // define the range for y
    
    for(int i=0;i<population.size();i++){ //Initialize the population
        population[i].x=rand_X(gen);
        population[i].y=rand_Y(gen);
        population[i].evaluateFitness();
    }
    sort(population.rbegin(),population.rend(),CompareIndividual());
}

    // Get high-resolution time point
    auto now = chrono::high_resolution_clock::now();

    // Convert time point to a number
    auto time_count = now.time_since_epoch().count();


    // Combine the high-resolution time with the thread ID hash
    unsigned seed = static_cast<unsigned>(time_count);

    mt19937 gen(seed); // Seed the generator with current time
    uniform_int_distribution<> rand_p1(0, 9); // define the range for x
    uniform_int_distribution<> rand_p2(0, 8); // define the range for y


    
void evolution(vector<individual> &population,vector<individual> &new_population){




    int parent1 = rand_p1(gen);
    int offset = rand_p2(gen) % 9 + 1;
    int parent2 = (parent1+offset) % 10;

    individual new_gen1;
    individual new_gen2;

    new_gen1.x=population[parent1].x; new_gen1.y=population[parent2].y;
    new_gen2.x=population[parent2].x; new_gen2.y=population[parent1].y;

    int mutate = rand() %  1001;    

    if(mutate>500){
        if(mutate>900){
            new_gen1.x+=0.15;
            new_gen1.y+=0.15;
            }
        else if(mutate>700){
            new_gen1.x-=0.15;
            new_gen1.y-=0.15;}    
        else if(mutate>600){
            new_gen1.x+=0.15;
            new_gen1.y-=0.15;}
        else if(mutate>500){
            new_gen1.x-=0.15;
            new_gen1.y+=0.15;}                        
        if(new_gen1.x<LOWER_X) new_gen1.x=LOWER_X;
        else if(new_gen1.x>UPPER_X) new_gen1.x=UPPER_X;
        if(new_gen1.y<LOWER_Y) new_gen1.y=LOWER_Y;
        else if(new_gen1.y>UPPER_Y) new_gen1.y=UPPER_Y;
    }

    mutate = rand() %  1001;    

    if(mutate>500){
        if(mutate>900){
            new_gen2.x+=0.15;
            new_gen2.y+=0.15;
            }
        else if(mutate>700){
            new_gen2.x-=0.15;
            new_gen2.y-=0.15;}    
        else if(mutate>600){
            new_gen2.x+=0.15;
            new_gen2.y-=0.15;}
        else if(mutate>500){
            new_gen2.x-=0.15;
            new_gen2.y+=0.15;}           
        if(new_gen2.x<LOWER_X) new_gen2.x=LOWER_X;
        else if(new_gen2.x>UPPER_X) new_gen2.x=UPPER_X;
        if(new_gen2.y<LOWER_Y) new_gen2.y=LOWER_Y;
        else if(new_gen2.y>UPPER_Y) new_gen2.y=UPPER_Y;
    }
    new_gen1.evaluateFitness();
    new_gen2.evaluateFitness();
    new_population.push_back(new_gen1);
    new_population.push_back(new_gen2);

}

void showPopulation(vector<individual>& population){
    cout<<population[0].x<<" "<<population[0].y<<" "<<population[0].f<<"\n";
//     for(auto x:population){
//         cout<< x.x <<" "<< x.y <<" "<< x.f <<"\n";
//     }
// cout<<"\n";
}


int main(){
 #ifndef ONLINE_JUDGE

    freopen("output.txt", "w", stdout);

#endif
    ofstream fout(getenv("OUTPUT_PATH"));


    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n=10;
    vector<individual> population(n);
    initializePopulation(population);

    vector<individual>new_population;

    showPopulation(population);

    srand(time(nullptr));
    float last_avg_fitness = calculateAverageFitness(population);
    float improvement_threshold = 0.005; // 0.1% improvement threshold
    bool continue_evolution = true;

for(int i=0;i < 50 && continue_evolution;i++){

    for(int j=0;j<(n/2);j++){

    evolution(population,new_population);

    }
    compareGens(population,new_population);
    
    new_population.clear();

  float current_avg_fitness = calculateAverageFitness(population);
        float improvement = (current_avg_fitness - last_avg_fitness)/100; // / last_avg_fitness;

        if (improvement < improvement_threshold) {
            continue_evolution = false;
        } else {
            last_avg_fitness = current_avg_fitness;
        }

    showPopulation(population);

}


    cout<<flush;
    return 0;
}