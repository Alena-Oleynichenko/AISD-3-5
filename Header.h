#include <iostream>
#include <time.h>
#include <complex>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

enum class CardinalDirection { NORTH, EAST, SOUTH, WEST };

template <class T, T True, T False>
class image {

    size_t columns, rows;
    vector<vector<T>> data;

public:
    image() = default;
    image(const size_t colls, const size_t rolls);
    image(const image& m2) = default;
    ~image()=default;
    int get_size() const {
        if ((columns == NULL) || (rows == NULL)) throw "Exeption";
        return columns * rows;
    }
    T GetMij( size_t i,size_t j) const;
    void SetMij(size_t i, size_t j, T new_val);
    bool can_multiply(const image& m2);
    image operator+(const image& m2);
    image operator*(const image& m2);
    image operator!();
    image operator=(const image& m2);
    image operator*(bool value);
    image operator+ (bool value);
    void random();
    T rand_();
    bool draw();
    void print();   
    double coefficient();
    auto Begin() {
        return data.begin();
    }
    auto End() {
        return data.end();
    }
    int get_rows() const;
    int get_cols() const;
};

template <class T, T True, T False>
image< T, True, False>::image(const size_t colls, const size_t rolls)
{
    columns = colls;
    rows = rolls;
    data.assign(columns, vector<T>(rows));
}

template <class T, T True, T False>
T image< T, True, False>::GetMij(size_t i, size_t j) const {

    if ((i >= rows) || (j >= columns) || (i < 0) || (j < 0)) throw "Invalid index";
    return data[i][j];

}

template <class T, T True, T False>
void image< T, True, False>::SetMij(size_t i, size_t j, T value) {

    if ((value == True) || (value == False))
    {
        if ((i < 0) || (i >= rows))
            return;
        if ((j < 0) || (j >= columns))
            return;
        else data[i][j] = value;
    }
}



template <class T, T True, T False>
bool image< T, True, False>::can_multiply(const image& m2) {

    return ((columns == m2.columns) && (rows == m2.rows));
}


template <class T, T True, T False>
T image< T, True, False>::rand_() {
    
    if (rand() % 2) return (True); else return (False);
}


template <class T, T True, T False>
void image< T, True, False>::random() {

    if ((columns == NULL) || (rows == NULL)) throw "Image is empty";
    srand(time(0));
    for (auto t1 = data.begin(); t1 != data.end(); t1++) {
        for (auto t2 = t1->begin(); t2 != t1->end(); t2++)
            *t2 = rand_();
    }

}


template <class T, T True, T False>
image< T, True, False> image< T, True, False>:: operator+(const image& m2) {

    if (!(can_multiply(m2))) {
        throw ("The images are of different sizes");
        image empty;
        return empty;
    }
    else {
        image m3(columns, rows);
        for (size_t i = 0; i < m3.get_cols(); i++) {
            for (size_t j = 0; j < m3.get_rows(); j++) {
                m3.data[i][j] = data[i][j] || m2.data[i][j];
            }
        }
        return m3;
    }
}

template <class T, T True, T False>
image< T, True, False> image< T, True, False>:: operator*(const image& m2) {

    if (!(can_multiply(m2))) {
        image empty;
        return empty;
    }
    else
    {
        image m3(columns, rows);
        for (size_t i = 0; i < columns; i++) {
            for (size_t j = 0; j < m2.rows; j++) {
                m3.data[i][j] = data[i][j] && m2.data[i][j];
            }
        }
        return m3;
    }
}

template <class T, T True, T False>
image< T, True, False> image< T, True, False>:: operator!() {

    image m3(columns, rows);
    for (size_t i = 0; i < columns; i++) {
        for (size_t j = 0; j < rows; j++) {
            m3.data[i][j] = !data[i][j];
        }
    }
    return m3;
}

template <class T, T True, T False>
image< T, True, False> image< T, True, False>::operator=(const image& m2) {

    image m3(m2);
    return m3;
}

template <class T, T True, T False>
image< T, True, False> image< T, True, False>:: operator*(bool value) {

    image m3(columns, rows);
    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; j++) {
            m3.data[i][j] = data[i][j] && value;
        }
    }
    return m3;
}

template <class T, T True, T False>
image< T, True, False> image< T, True, False>:: operator+ (bool value) {

    image m3(columns, rows);
    for (size_t i = 0; i < columns; i++) {
        for (size_t j = 0; j < rows; j++) {
            if ((value) || (data[i][j] == True)) m3.data[i][j] = data[i][j] || value;
        }
    }
    return m3;
}

template <class T, T True, T False>
bool image< T, True, False>::draw() {
    cout << "Size of image: " << columns << 'x' << rows << endl << "'" << True << "' - is *\n" << "'" << False << "' - is ^\n\n";
    size_t a = 1;
    T f;
    for (auto t1 = data.begin(); t1 != data.end(); t1++) {
        for (auto t2 = t1->begin(); t2 != t1->end(); t2++) {
            cout <<  a << ':';
            cin >> f;
            *t2 = f;
            a++;
        }
    }
    cout << endl;
    return true;
}


template <class T, T True, T False>
void image< T, True, False>::print() {


    for (auto t1 = data.begin(); t1 != data.end(); t1++) {
        for (auto t2 = t1->begin(); t2 != t1->end(); t2++)
            if (*t2 == True) cout << "1" << " ";
            else if (*t2 == False) cout << "*" << " ";
        cout << endl;
    }
    cout << endl;
}


template <class T, T True, T False>
double image< T, True, False>::coefficient() {

    size_t a1 = 0;
    size_t all = get_size();
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (data[i][j] == True)
                a1++;
        }
    }
    if (a1 == 0)
        return 0;
    else
    {
        return (double)a1 /(double)all;
    }
}



template <class T, T True, T False>
int image<T, True, False>::get_rows() const {

    if (rows == NULL) throw "exeption";
    return rows;
}

template <class T, T True, T False>
int  image<T, True, False>::get_cols() const {

    if (columns == NULL) throw "exeption";
    return columns;
}
