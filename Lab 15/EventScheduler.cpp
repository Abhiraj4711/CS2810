#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class Event
{
public:
    int startTime;
    int endTime;
    Event(int start, int end)
    {
        startTime = start;
        endTime = end;
    }
    virtual double calculateProfit() const = 0;
    ~Event();
    friend void operator>>(std::istream &stream, Event *&E);
};
Event::~Event() {}

class Concert : public Event
{
public:
    int startTime;
    int endTime;
    int ticketPrice;
    int ticketSold;
    int artistFee;
    int logisticCost;
    Concert() : Event(0, 0)
    {
    }
    Concert(int start, int end, int TicketPrice, int TicketSold, int ArtistFee, int LogisticCost) : Event(start, end)
    {
        startTime = start;
        endTime = end;
        ticketPrice = TicketPrice;
        ticketSold = TicketSold;
        artistFee = ArtistFee;
        logisticCost = LogisticCost;
    }
    double calculateProfit() const override
    {
        /*Profit Secrets:
        Revenue: Ticket Revenue = (Ticket Price * Tickets Sold)
        Ticket Revenue = Ticket Revenue - 0.18*Ticket Revenue
        Cost: Sum of total cost (artist fees and logistics).
        Profit: Revenue - Cost
        Net Profit = (profit>2*cost)? 0.7* profit : profit.  */
        double ticketRevenue = (ticketPrice * ticketSold);
        ticketRevenue = ticketRevenue - 0.18 * ticketRevenue;
        double cost = artistFee + logisticCost;
        double profit = ticketRevenue - cost;
        double netProfit = profit > 2 * cost ? 0.7 * profit : profit;
        return netProfit;
    }
};

class TheaterShow : public Event
{
public:
    int startTime;
    int endTime;
    int baseTicketPrice;
    int totalSeats;
    int venueCost;
    TheaterShow() : Event(0, 0) {}
    TheaterShow(int start, int end, int BasePrice, int TotalSeats, int VenueCosts) : Event(start, end)
    {
        startTime = start;
        endTime = end;
        baseTicketPrice = BasePrice;
        totalSeats = TotalSeats;
        venueCost = VenueCosts;
    }
    double calculateProfit() const override
    {
        /*Profit Secrets:
        Ticket Revenue: 0.25 * Total seats * (2 * Base Ticket Price) + 0.75 * Total Seats * Base Ticket Price.
        Ticket Revenue= Ticket Revenue - 0.18 * Ticket Revenue.
        Popcorn Price =150
        Popcorn Revenue: 0.25 * Total Seats * Popcorn Price.
        Net Profit: Ticket Revenue+ Popcorn Revenue- venue cost.
        Note : Total seats attribute is always divisible by 4.*/

        double totalRevenue = totalSeats / 4 * (2 * baseTicketPrice) + 3 * totalSeats / 4 * baseTicketPrice;
        totalRevenue = totalRevenue - totalRevenue * 0.18;
        double popcornPrice = 150;
        double popcornRevenue = totalSeats / 4 * popcornPrice;
        double netProfit = totalRevenue + popcornRevenue - venueCost;
        return netProfit;
    }
};

class Wedding : public Event
{
public:
    int startTime;
    int endTime;
    int baseAmount;
    int decorationCost;
    int guestCount;
    int venueCost;
    Wedding() : Event(0, 0) {}
    Wedding(int start, int end, int BaseAmount, int DecorationCost, int GuestCount, int VenueCost) : Event(start, end)
    {
        startTime = start;
        endTime = end;
        baseAmount = BaseAmount;
        decorationCost = DecorationCost;
        guestCount = GuestCount;
        venueCost = VenueCost;
    }
    double calculateProfit() const override
    {
        /*Profit Secrets:
        Total Venue Cost: (Guestcount > 200) ? Venue Cost*3 : Venue Cost
        Catering Cost: (Guest Count > 100) ? Guest Count * 70 :  Guest Count * 100 .
        Net Profit: Base amount - Total Venue Cost - decoration Cost -  catering costs. */

        double totalVenueCost = guestCount > 200 ? venueCost * 3 : venueCost;
        double cateringCost = guestCount > 100 ? guestCount * 70 : guestCount * 100;
        double netProfit = baseAmount - totalVenueCost - decorationCost - cateringCost;
        return netProfit;
    }
};

struct comparator
{
    bool operator()(Event *&a, Event *&b)
    {
        if (a->startTime == b->startTime)
            return a->endTime < b->endTime;
        return a->startTime < b->startTime;
    }
};

void operator>>(std::istream &stream, Event *&E)
{
    int type;
    stream >> type;
    if (type == 1)
    {
        int start, end, TicketPrice, TicketsSold, ArtisteFee, LogisticCost;
        stream >> start >> end >> TicketPrice >> TicketsSold >> ArtisteFee >> LogisticCost;
        E = new Concert(start, end, TicketPrice, TicketsSold, ArtisteFee, LogisticCost);
    }
    else if (type == 2)
    {
        int start, end, BasePrice, TotalSeats, VenueCosts;
        stream >> start >> end >> BasePrice >> TotalSeats >> VenueCosts;
        E = new TheaterShow(start, end, BasePrice, TotalSeats, VenueCosts);
    }
    else
    {
        int start, end, BaseAmount, DecorationCost, GuestCount, VenueCost;
        stream >> start >> end >> BaseAmount >> DecorationCost >> GuestCount >> VenueCost;
        E = new Wedding(start, end, BaseAmount, DecorationCost, GuestCount, VenueCost);
    }
}

class EventScheduler
{
public:
    vector<Event *> allEvents;
    EventScheduler(int n)
    {
        allEvents.resize(n);
    }
    void takeInput(int n)
    {
        for (int i = 0; i < n; i++)
        {
            Event *E;
            cin >> E;
            allEvents[i] = E;
        }
        comparator comp;
        sort(allEvents.begin(), allEvents.end(), comp);
    }
    double findMaxProfit()
    {
        int n = (int)allEvents.size();
        vector<double> dp(1002, 0.0f);
        vector<double> allProfits(n);
        map<int, vector<int>> mapOfStartTimes;
        for (int i = 0; i < n; i++)
        {
            allProfits[i] = allEvents[i]->calculateProfit();
            mapOfStartTimes[allEvents[i]->startTime].push_back(i);
        }
        for (int i = 0; i < 1002; i++)
        {
            if (i != 0)
            {
                dp[i] = max(dp[i], dp[i - 1]);
            }
            vector<int> &Events = mapOfStartTimes[i];
            for (auto index : Events)
            {
                dp[allEvents[index]->endTime] = max(dp[allEvents[index]->endTime], dp[i] + allProfits[index]);
            }
        }
        return dp.back();
    }
};

int main()
{
    int n;
    cin >> n;
    EventScheduler es(n);
    es.takeInput(n);
    cout << fixed << setprecision(2) << es.findMaxProfit() << "\n";
}
