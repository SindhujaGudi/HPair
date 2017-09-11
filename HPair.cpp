


//Header Files
#include <bits/stdc++.h>
#define DEBUG true

using namespace std;

// TravelingPairs Class

 // holds Origin city and destination city
 
class TravelingPairs{

    string origin; //Origin City
    string dest; //destination City

public:
    // Zero args constuctor
    TravelingPairs() {
        origin = "";
        dest = "";
    }

  // Constructor with origin  city and destination city arguments
    
    TravelingPairs(string o, string d) {
        this->origin = o;
        this->dest = d;
    }

    //getter for origin  city
    string getOrigin () {
        return origin;
    }

   //getter for destination city
    string getDestination() {
        return dest;
    }
};

/*
   Function: readCityDataFile
   Read cities from the given filename
   Parameters:
      fileName - Filename
   Returns:
      vector readData

*/
vector<string> readCityDataFile(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName.c_str());

    vector<string> citiesValues;

    if (!inputFile) {
        cout << "Invalid! unable to open the file. Please check the file : " << fileName << endl;
        return citiesValues;
    }
    string input;
    while (inputFile >> input) {
    	citiesValues.push_back(input);
    }
    //Close the cities file
    inputFile.close();

    return citiesValues;
}

/*
   Function: readPairsFromTheFile
   Read Pairs from the FlightDetails and userReq 
   Parameters:
      fileName - Filename
   Returns:
      vector TravelingPairs

*/
vector<TravelingPairs> readPairsFromTheFile(string fileName) {

	string origin;
	string destination;

	ifstream inputFile;
    inputFile.open(fileName.c_str());

    vector<TravelingPairs> pairsData;

    if (!inputFile) {
        cout << "Invalid! unable to open the file. Please check the file : " << fileName << endl;
        return pairsData;
    }

    while(inputFile >> origin >> destination) {
    	pairsData.push_back(TravelingPairs(origin, destination));
    }
    //Close the flightDetails or userreq
    inputFile.close();

    return pairsData;
}

/*
   Function: isValidFlightRoute
   Verify the requested route with Flight route whether it is valid or not
   Parameters:
      origin - Origin city
      dest - Destination city
      flights - Pair
      sizeOfFlights- Flight vector size
      reached - Reached map
   Returns:
      bool valid/not

*/
bool isValidFlightRoute(string origin, string dest, TravelingPairs* flights, int sizeOfFlights, map<string, bool> reached) {

    if (origin == dest) {

         if (DEBUG) {

             cout << "\t valid:Reached Destination city " << dest << endl;
        }
    	// Flight reached the destination city
    	return true;
    } else {

        if (reached.find(origin) == reached.end()) {
            reached[origin] = true;
        } else {

              if (DEBUG) {

                  cout << "\t\t Backtracking: " << origin << endl;

                  }
           // Already Reached
            return false;
        }

        for (int i = 0; i < sizeOfFlights; i++) {
            if ((flights[i].getOrigin() == origin)) {

                 if (DEBUG) {

                     cout << "\t HPAir travels from " + origin + " to " + flights[i].getDestination() << endl;

                     }
                if (isValidFlightRoute(flights[i].getDestination(), dest, flights, sizeOfFlights, reached)) {
                    return true;
                }
            }
        }

         if (DEBUG) {
            cout << "\t\t Hits Deadend " << origin << ". Traverse back." << endl;

            }
       //No flights
        return false;
    }
}


/*
   Function: main
   Check the RequestedFlightFile pairs are valid with FlightFile data
   Returns:
      int success (0) /fail of method (1)

*/
int main() {

    vector<string> cities = readCityDataFile("Cities.txt");
    vector<TravelingPairs> flights = readPairsFromTheFile("FlightDetails.txt");
    vector<TravelingPairs> requests = readPairsFromTheFile("UserReq.txt");

    TravelingPairs* flightsFilePairs = &flights[0];
    TravelingPairs* requestdFilePairs = &requests[0];
    map<string, bool> reached;

    //Verify the cities are valid or not in FlightFile with cities file
    for (vector<TravelingPairs>::iterator it = flights.begin(); it != flights.end(); ++it) {
        if ((find(cities.begin(), cities.end(), (*it).getOrigin()) == cities.end())) {
            cout << (*it).getOrigin() << "City not found. Please check the Cities file|Line 154" << endl;
            exit(0);
        }
        if((find(cities.begin(), cities.end(), (*it).getDestination()) == cities.end())) {
            cout << (*it).getDestination() << "City not found. Please check the Cities file|Line 158" << endl;
            exit(0);
        }
    }

    //Verify the cities are valid or not in RequestedFlightFile with cities file
    for (vector<TravelingPairs>::iterator it = requests.begin(); it != requests.end(); ++it) {
        if ((find(cities.begin(), cities.end(), (*it).getOrigin()) == cities.end())) {
            cout << (*it).getOrigin() << "City not found. Please check the Cities file|Line 166" << endl;
            exit(0);
        }
        if((find(cities.begin(), cities.end(), (*it).getDestination()) == cities.end())) {
            cout << (*it).getDestination() << "City not found. Please check the Cities file|Line 170" << endl;
            exit(0);
        }
    }

    //Check the RequestedFlightFile pairs are valid with FlightFile data
     for (int i = 0; i < requests.size(); i++) {
        if (isValidFlightRoute(requestdFilePairs[i].getOrigin(), requestdFilePairs[i].getDestination(), flightsFilePairs, flights.size(), reached)) {
            cout << "HPAir travels from " << requestdFilePairs[i].getOrigin() << " to " << requestdFilePairs[i].getDestination() << endl;
        } else {
            cout << "Sorry, HPAir does NOT travel from " << requestdFilePairs[i].getOrigin() << " to " << requestdFilePairs[i].getDestination() << endl;
        }
    }
    return 0;
}
