#include "Package.h"

unsigned int Package::ID = 0;

Package::Package(Vertex * pickUp, Vertex * delivery) :
id(Package::ID), pickUp(pickUp), delivery(delivery)
{
    Package::ID++;
}
Package::Package(const Package& aPackage) = default;

unsigned int Package::getId() const { return id; }

Vertex * Package::getDelivery() const { return delivery; }
void Package::setDelivery(Vertex * dVertex) { delivery = dVertex; }

Vertex * Package::getPickUp() const { return pickUp; }
void Package::setPickUp(Vertex * pickUpVertex) { pickUp = pickUpVertex; }

bool Package::operator==(const Package &rhs) const { return delivery == rhs.delivery && pickUp == rhs.pickUp; }
std::ostream &operator<<(std::ostream &os, const Package &aPackage)
{
    os << "id: " << aPackage.id << std::endl <<
    "pickUp: " << *aPackage.pickUp << std::endl << "delivery: " << *aPackage.delivery << std::endl;
    return os;
}
