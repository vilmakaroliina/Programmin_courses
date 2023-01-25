// Datastructures.cc
//
// Student name: Vilma Lehto
// Student email: vilma.lehto@tuni.fi
// Student number:50044139

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::station_count()
{
    int count = stations_.size();
    return count;
}

void Datastructures::clear_all()
{
    stations_.clear();
    regions_.clear();
}

std::vector<StationID> Datastructures::all_stations()
{
    std::vector<StationID> ids;
    ids.reserve(stations_.size());
    auto end = stations_.end();
    for (auto iter = stations_.begin(); iter != end; ++iter){
        ids.push_back(iter->first);
    }
    return ids;

}

bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    double distance = sqrt(xy.x*xy.x+xy.y*xy.y);
    Station newStation = {.ID = id, .name = name, .coordinates = xy, .distance = distance};

    //declare a pair for the return values from insert
    std::pair <std::unordered_map<std::string, Station>::iterator, bool> ptr;
    ptr = stations_.insert({id, newStation});

    //lisätään myös toiseen mappiin
    station_by_coord_.insert({xy, id});

    return ptr.second;

}

Name Datastructures::get_station_name(StationID id)
{
    for(auto elem : stations_){
        if (elem.first == id){
            return elem.second.name;
        }
    }
    return NO_NAME;
    /*auto iter = stations_.find(id);
    if (iter != stations_.end()){
        return iter->second.name;
    }
    else {
        return NO_NAME;
    }*/
}

Coord Datastructures::get_station_coordinates(StationID id)
{
    auto iter = stations_.find(id);
    if (iter != stations_.end()){
        return iter->second.coordinates;
    }
    else {
        return NO_COORD;
    }
}

//tästä pitää kysyä apuaaaa! Miten tehdä järkevästi //NIMEN MUKAAN!
std::vector<StationID> Datastructures::stations_alphabetically()
{
    std::vector<std::pair<StationID, Station>> stationVec;
    stationVec.reserve(stations_.size());
    stationVec.assign(stations_.begin(), stations_.end()); //O(n)
    auto begin = stationVec.begin();
    auto end = stationVec.end();
    std::sort(begin, end, [](auto a, auto b){
        return a.second.name < b.second.name;});  //O(n)
    std::vector<StationID> stationIDs;
    while(begin != end){  //O(n)
       stationIDs.push_back(begin->first);
       ++begin;
    }
    return stationIDs;

}

std::vector<StationID> Datastructures::stations_distance_increasing()
{
    std::vector<std::pair<StationID, Station>> stationVec;
    stationVec.reserve(stations_.size());
    stationVec.assign(stations_.begin(), stations_.end()); //O(n)
    auto begin = stationVec.begin();
    auto end = stationVec.end();
    std::sort(begin, end, [](auto a, auto b){
        return a.second.distance < b.second.distance;});  //O(n)
    std::vector<StationID> stationIDs;
    while(begin != end){  //O(n)
       stationIDs.push_back(begin->first);
       ++begin;
    }
    return stationIDs;
}

StationID Datastructures::find_station_with_coord(Coord xy)
{   auto *id = &station_by_coord_.at(xy);
    if (id != nullptr){
        return *id;
    }
    return NO_STATION;
}

bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    auto *station = &stations_.at(id);
    if (station != nullptr){
        Coord oldCoordinates = (*station).coordinates;
        (*station).coordinates = newcoord;
        double newDistance = sqrt(newcoord.x*newcoord.x+newcoord.y*newcoord.y);
        (*station).distance = newDistance;
        station_by_coord_.erase(oldCoordinates);
        station_by_coord_.insert({newcoord, id});
        return true;
    }
    return false;
}

bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    auto *station = &stations_.at(stationid);
    if (station != nullptr){
        auto iter = station->testDep_.find({time, trainid});
        if (iter == station->testDep_.end()){
            station->testDep_.insert({time, trainid});
            return true;
        }
    }
    return false;

}

bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    auto *station = &stations_.at(stationid);
    if (station != nullptr){
        auto iter = station->testDep_.find({time, trainid});
        if (iter != station->testDep_.end())
        {
            station->testDep_.erase(iter);
            return true;
        }
    }
    return false;
}

std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    std::vector<std::pair<Time, TrainID>> after;
    auto *station = &stations_.at(stationid);
    if (station != nullptr){
        auto depEnd = station->testDep_.end();
        auto depIter = station->testDep_.begin();

        while(depIter!= depEnd){
            if(depIter->first >= time){
                after.push_back(*depIter);
            }
            ++depIter;
        }
    }
    else {
        std::pair<Time, TrainID> emptyPair = {NO_TIME, NO_TRAIN};
        after.push_back(emptyPair);
    }
    return after;
}

bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    Region newRegion;
    newRegion.id = id;
    newRegion.name = name;
    newRegion.coordinates = coords;
    //declare a pair for the return values from insert
    std::pair <std::unordered_map<RegionID, Region>::iterator, bool> resultPair;
    resultPair = regions_.insert({id, newRegion});
    return resultPair.second;
}

std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> regions;
    regions.reserve(regions_.size());
    for(auto pair : regions_){
        regions.push_back(pair.first);
    }
    return regions;
}

Name Datastructures::get_region_name(RegionID id)
{
    auto iter = regions_.find(id);
    if (iter != regions_.end()){
        return iter->second.name;
    }
    else {
        return NO_NAME;
    }
}

std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    auto iter = regions_.find(id);
    if (iter != regions_.end()){
        return iter->second.coordinates;
    }
    else {
        std::vector<Coord> noCoord {NO_COORD};
        return noCoord;
    }
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    Region* child;
    Region* parent;
    auto end = regions_.end();
    for (auto iter = regions_.begin(); iter != end; ++iter){
        if (iter->first == id){
            child = &iter -> second;
        }
        else if (iter -> first == parentid){
            parent = &iter -> second;
        }
    } //so far O(n)


    if (child != nullptr && parent != nullptr){ //tarkistus, että molemmat on olemassa
        if ((*child).parent == nullptr ){ //tarkitetaan onko childilla jo parent
            (*child).parent = parent;
            return true;
        }
    }
    return false;


}

bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    Station *station = &stations_.at(id); //O(1) at worst
    Region *parent = &regions_.at(parentid); //O(1) at worst
    if(station != nullptr && parent != nullptr){ //0(1), tarkistetaan että molemmat on olemassa
        if((*station).region == nullptr){
            station->region = parent;
            return true;
        }
    }
    return false;
}

std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    std::vector<RegionID> parentRegions;
    auto station = stations_.find(id); //O(1)
    if (station == stations_.end()){ //O(1)
       parentRegions.push_back(NO_REGION);
       return parentRegions;
    }
    else if (station ->second.region == nullptr){ //O(1)
        return parentRegions;
    }

    Region region = *(station->second.region);
    while(true){
        parentRegions.push_back(region.id);
        if (region.parent == nullptr){
            break;
        }
        else{
            region = *region.parent; //0(1)
        }
    }
    return parentRegions;

}

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("all_subregions_of_region()");
}

std::vector<StationID> Datastructures::stations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("stations_closest_to()");
}

bool Datastructures::remove_station(StationID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_station()");
}

RegionID Datastructures::common_parent_of_regions(RegionID /*id1*/, RegionID /*id2*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("common_parent_of_regions()");
}

//kaatuu tässä funktiossa, koska out of range, todennäkösesti koska nextStation
bool Datastructures::add_train(TrainID trainid, std::vector<std::pair<StationID, Time> > stationtimes)
{
    //tarkistetaan onko juna jo olemassa
    if(trains_.find(trainid) != trains_.end()){ //O(n), poikkeustapaus
        return false;
    }

    for (auto stop : stationtimes){
        if (stations_.find(stop.first) == stations_.end()){
            return false;
        }
    } //O(n)

    //luodaan juna struct ja lisätään se settiin ja etsitään siihen pointteri
    Train train = {.trainid = trainid, .stationTimes = stationtimes}; //O(1)
    trains_.insert({trainid, train}); //palauttaa iteraattorin, voinko hydyntää sitä
    Train* leavingTrain = &trains_.at(trainid); //O(1)

    //silmukoidaan jokainen junan pysähdys läpi
    for (auto iter = stationtimes.begin();
         iter != stationtimes.end(); ++iter){ //silmukka O(n)

        //etsitään asema ja otetaan siihen iteraattori
        auto stationPair = stations_.find(iter->first); //O(1)

        //tarkistetaan onko jokainen asema olemassa
        if (stationPair == stations_.end()){ //O(1)
            return false;
        }

        //alustetaan seuraavan aseman pointteri
        Station *nextStation = nullptr;

        //tarkistetaan, että ei olla viimeisessä asemassa
        if (iter != stationtimes.end() - 1) {

            //haetaan pointteri seuraavaan asemaan
            ++iter;
            nextStation = &stations_.at(iter->first);
            --iter;

            //lisätään jokaiseen asemaan tieto niiden seuraavista asemista
            stationPair->second.trainsFromStation.insert({nextStation, leavingTrain});
        }

        //lisätään juna asemien pysähdyksiin, tässä virhe, sillä ohjelman
        //ei pitänyt tehdä mitään, jos edes yksi asemista ei ole oikein
        stationPair->second.testDep_.insert({iter->second, trainid}); //O(1)


    }
    return true;
}

std::vector<StationID> Datastructures::next_stations_from(StationID id)
{
    //otetaan pointeri haluttuun asemaan ja luodaan palautus vektori
    auto StationIter = stations_.find(id); //O(1)
    std::vector<StationID> nextStations;

    //käsitellään erikoistapaus pois alta
    if(StationIter == stations_.end()){
        nextStations.push_back(NO_STATION);
        return nextStations;
    } //O(1)

    Station* ogStation = &stations_.at(id);

    //kerätään vektoriin asemalta lähtevien junien seuraavat junat
    for(auto &station : ogStation->trainsFromStation){
           nextStations.push_back(station.first->ID);
    }

    return nextStations;
}

std::vector<StationID> Datastructures::train_stations_from(StationID stationid, TrainID trainid)
{
    std::vector<StationID> nextStations;

    auto trainIter = trains_.find(trainid);
    auto stationIter = stations_.find(stationid);

    if (trainIter == trains_.end() || stationIter == stations_.end()){
        nextStations.push_back(NO_STATION);
        return nextStations;
    }

    Train *train = &trains_.at(trainid);

    nextStations.reserve(train->stationTimes.size());

    bool currentStation = false;
    auto end = train->stationTimes.end();
    for (auto iter = train->stationTimes.begin(); iter != end; ++iter){ //O(n)
        if (currentStation == true){
            nextStations.push_back(iter->first);
        }

        if (iter->first == stationid){
            currentStation = true;
        }
    }

    if (nextStations.empty()){
        nextStations.push_back(NO_STATION);
    }
    return nextStations;
}

void Datastructures::clear_trains()
{
    for(auto &stationPair : stations_){ //O(n)
        stationPair.second.trainsFromStation.clear(); //O(1)
        stationPair.second.departures.clear(); //O(1)
    }
    trains_.clear(); //O(1)
}

std::vector<std::pair<StationID, Distance>> Datastructures::route_any(StationID fromid, StationID toid)
{
    std::vector<std::pair<StationID, Distance>> route;
    //etsitään lähtö ja tavoite asemat
    auto begin = stations_.find(fromid);
    auto end = stations_.find(toid);

    if (begin == stations_.end() || end == stations_.end()){
        route.push_back({NO_STATION, NO_DISTANCE});
        return route;
    }

    Station *beginStation = &stations_.at(fromid);

    //alustetaan jokainen station
    for (auto &station : stations_){
        station.second.color = 0;
        station.second.distFromStation = -1;
        station.second.parent = nullptr;
    }

    //alustetaan jono sekä lähtö ja lisätään lähtö jonoon
    std::queue<Station*> q;
    beginStation->color = 1;
    beginStation->distFromStation = 0;
    q.push(beginStation);

    while(!q.empty()){
        Station *current = q.front();
        q.pop();

        //Tarkistetaan onko käsittelyssä oleva asema määränpää
        if (current->ID == toid){
            route.push_back({current->ID, current->distFromStation});
            Station *whereFrom = current->parent;

            //otetaan talteen reitti, jota pitkin päädyttiin määränpäähän
            while (whereFrom != nullptr){
                route.push_back({whereFrom->ID, whereFrom->distFromStation});
                whereFrom = whereFrom->parent;
            }
            break;
        }
        for (auto station : current->trainsFromStation){

            if (station.first->color == 0){
                //vaihdetaan väri harmaaksi ja lisätään vanhempi
                station.first->color = 1;
                station.first->parent = current;

                //lasketaan etäisyys
                int currentX = current->coordinates.x;
                int currentY = current->coordinates.y;
                int X = station.first->coordinates.x;
                int Y = station.first->coordinates.y;

                int dist = current->distFromStation +
                        sqrt((currentX-X)*(currentX-X)+
                             (currentY-Y)*(currentY-Y));
                station.first->distFromStation = dist;

                //lisätään asema jonoon
                q.push(station.first);
            }
        }
        current->color = 2;

    }
    std::reverse(route.begin(), route.end());
    return route;
}

std::vector<std::pair<StationID, Distance>> Datastructures::route_least_stations(StationID /*fromid*/, StationID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_least_stations()");
}

std::vector<StationID> Datastructures::route_with_cycle(StationID /*fromid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_with_cycle()");
}

std::vector<std::pair<StationID, Distance>> Datastructures::route_shortest_distance(StationID /*fromid*/, StationID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_shortest_distance()");
}

std::vector<std::pair<StationID, Time>> Datastructures::route_earliest_arrival(StationID /*fromid*/, StationID /*toid*/, Time /*starttime*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_earliest_arrival()");
}
