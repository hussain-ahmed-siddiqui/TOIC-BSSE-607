#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TMultiGraph.h"

void plot() {
    // Open the output file
    ifstream inputFile("output.txt");
    float x, y, fitness;
    int generation = 0;

    TGraph *graphFitness = new TGraph();
    TGraph *graphX = new TGraph();
    TGraph *graphY = new TGraph();

    while (inputFile >> x >> y >> fitness) {
        graphFitness->SetPoint(generation, generation, fitness);
        graphX->SetPoint(generation, generation, x);
        graphY->SetPoint(generation, generation, y);
        generation++;
    }
    inputFile.close();

    // Create a canvas and divide it into three pads
    TCanvas *c = new TCanvas("c", "Evolutionary Algorithm Progress", 1200, 900);
    c->Divide(1, 3);

    // Plot Fitness
    c->cd(1);
    graphFitness->SetTitle("Fitness Evolution;Generation;Fitness");
    graphFitness->SetMarkerStyle(21);
    graphFitness->SetMarkerColor(kBlue);
    graphFitness->Draw("APL");

    // Plot X values
    c->cd(2);
    graphX->SetTitle("X Value Evolution;Generation;X Value");
    graphX->SetMarkerStyle(21);
    graphX->SetMarkerColor(kRed);
    graphX->Draw("APL");

    // Plot Y values
    c->cd(3);
    graphY->SetTitle("Y Value Evolution;Generation;Y Value");
    graphY->SetMarkerStyle(21);
    graphY->SetMarkerColor(kGreen);
    graphY->Draw("APL");

    // Update the canvasj
    c->Update();
}
