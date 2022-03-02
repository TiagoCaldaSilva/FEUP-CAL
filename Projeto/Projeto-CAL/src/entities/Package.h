#ifndef E_STAFETAS_PACKAGE_H
#define E_STAFETAS_PACKAGE_H

#include <ostream>
#include "../graph/GraphElements.h"

class Package {
public:
    /**
     * @brief Package's constructor
     * @param pickUp Vertex where the package should be picked up
     * @param delivery Vertex where the package should be delivered
     */
    Package(Vertex * pickUp, Vertex * delivery);
    /**
     * @brief Package's copy constructor
     * @param aPackage Package to copy
     */
    Package(const Package& aPackage);
    /**
     * @brief Get the Package's id
     * @return Id value
     */
    unsigned int getId() const;

    /**
     * @brief Get the Package's delivery vertex
     * @return Package's delivery vertex
     */
    Vertex * getDelivery() const;
    /**
     * @brief Set the Package's delivery vertex
     * @param pVertex New delivery vertex
     */
    void setDelivery(Vertex * pVertex);

    /**
     * @brief Get the Package's pickUp vertex
     * @return Package's pickUp vertex
     */
    Vertex * getPickUp() const;
    /**
     * @brief Set the Package's pickUp vertex
     * @param pickUp New pickUp vertex
     */
    void setPickUp(Vertex * pickUp);

    /**
     * @param rhs Package to be compared
     * @return True if the compared packages are equal, false otherwise
     */
    bool operator==(const Package &rhs) const;
    /**
     * @brief Writes the Package info to os
     * @param os Ostream to be written with the Package's info
     * @param aPackage Package that should be used
     * @return os with the Package's info
     */
    friend std::ostream &operator<<(std::ostream &os, const Package &aPackage);

private:
    Vertex * delivery;
    Vertex * pickUp;

    unsigned int id;
    static unsigned int ID;
};

#endif // E_STAFETAS_PACKAGE_H
