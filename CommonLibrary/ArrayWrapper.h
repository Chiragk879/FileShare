#pragma once


namespace IMFS
{
    /// <summary>
    ///     Wrapper class for C-style arrays
    ///     This class only wraps the array but not takes
    ///     ownership. So passed array WON'T be deleted
    ///     by the wrapper class. This class denies any R/W
    ///     operation on stored array.
    /// </sumamry>
    template<typename T>
    class ArrayWrapper
    {
    public:

        /// Standart std-like typedefs
        typedef T value_type;
        typedef value_type& reference;
        typedef const reference const_reference;
        typedef value_type* pointer;
        typedef const pointer const_pointer;
        
        /// <sumamry>
        ///     Iterator class
        ///     helps to iterate through the array
        ///     but not read or write
        /// </summary>
        class iterator
        {
        public:
            iterator();
            inline iterator(const iterator& src) { *this = src; }
            const iterator& operator = (const iterator& src)
            {
                m_ulPos = src.m_ulPos; m_pArr = src.m_pArr; return *this;
            }
            inline iterator& operator++()
            { ++m_ulPos; return *this; }

            iterator operator++(int)
            { return iterator(m_pArr, m_ulPos++); }

            iterator& operator--()
            {   --m_ulPos; return *this; }

            iterator operator--(int)
            {   return iterator(m_pArr, m_ulPos--); }

            iterator operator + (size_t ulDelta)
            {   return iterator(m_pArr, m_ulPos + ulDelta); }

            iterator& operator += (size_t ulDelta)
            {   m_ulPos += ulDelta; return *this; }

            iterator operator - (size_t ulDelta)
            {   return iterator(m_pArr, m_ulPos - delta); }

            iterator& operator -= (size_t ulDelta)
            { m_ulPos -= delta; return iterator(m_pArr, m_ulPos); }

            bool operator == (const iterator& other) const
            {   return m_pArr == other.m_pArr && m_ulPos == other.m_ulPos; }

            inline bool operator != (const iterator& other) const { return !(*this == other); };

            inline size_t GetCurrentPosition() const { return m_ulPos; }
        protected:
            friend class ArrayWrapper;
            iterator(pointer pArr, size_t ulPos);
        private:
            pointer m_pArr;
            size_t m_ulPos;
        };

        ArrayWrapper(pointer pArr = nullptr, size_t ulSize = 0);
        inline ArrayWrapper(const ArrayWrapper& src) { *this = src; }
        const ArrayWrapper& operator = (const ArrayWrapper& src);

        /// <summary>
        ///     Swaps internal pointers
        /// </summary>
        void swap(ArrayWrapper& src);

        /// <summary>
        ///     Swaps internal pointers
        /// </summary>
        void swap(pointer& pArr, size_t& ulSize);

        /// <summary>
        ///     Returns iterator to the first element in array
        /// </summary>
        iterator begin() const { return iterator(m_pArr, 0); }

        /// <summary>
        ///     Returns iterator to the element right after the last
        ///     element
        /// </summary>
        iterator end() const { return iterator(m_pArr, m_ulSize); }

        /// <summary>
        ///     Returns size of the wrapped array
        ///
        inline size_t size() const { return m_ulSize; }

        /// <summary>
        ///     Checks arrays for emptyness(is array 0 sized?)
        /// <summary>
        inline bool empty() const { return size() == static_cast<size_t>(0); }

        /// <summary>
        ///     Checks if wrapped array is null
        /// <summary>
        inline bool null() const { return nullptr == m_pArr; }

        /// <summary>
        ///     Adds static_cast support to the stored array.
        /// </summary>
        operator pointer () { return const_cast<pointer>(m_pArr); }

        /// <summary>
        ///     Adds static_cast support to the stored array.
        /// </summary>
        operator const_pointer () const { return m_pArr;  }

    protected:
        pointer m_pArr;
        size_t m_ulSize;
    };

    /// <summary>
    ///     Allows only ReadOnly operations on the wrapped array
    /// </sumamry>
    template<typename T>
    class ReadOnlyArray: public ArrayWrapper<T>
    {
    public:
        ReadOnlyArray(pointer pArr, size_t ulSize) : ArrayWrapper(pArr, ulSize) {};
        ReadOnlyArray(const ArrayWrapper<T>& src) : ArrayWrapper(src) {}
        ReadOnlyArray& operator = (const ReadOnlyArray& src) { ArrayWrapper::operator = (src); return *this; }
        const const_reference operator[](size_t idx) const { return m_pArr[idx]; }
        const const_reference at(size_t idx) const { return m_pArr[idx]; }
    };

    /// <summary>
    ///     Allows write only operations on the stored array
    /// </summary>
    template<typename T>
    class WriteOnlyArray : public ArrayWrapper<T>
    {
    public:
        WriteOnlyArray(pointer pArr, size_t ulSize) : ArrayWrapper(pArr, ulSize) {};

        /// <summary>
        ///     Sets value in position specified by parameter idx
        /// <summary>
        void Set(const_reference value, size_t idx) const
        {
            if (size() > idx)
            {
                m_pArr[idx] = value;
            }
        }

        /// <summary>
        ///     Sets value in position specified by iterator pos
        /// <summary>
        void Set(const_reference value, const iterator pos) const { Set(value, pos.GetCurrentPosition()); }
    };

    template<typename T>
    ArrayWrapper<T>::iterator::iterator()
        : m_pArr(nullptr), m_ulPos(0UL)
    {}

    template<typename T>
    ArrayWrapper<T>::iterator::iterator(pointer pArr, size_t ulPos)
        : m_pArr(pArr), m_ulPos(ulPos)
    {}

    template<typename T>
    inline ArrayWrapper<T>::ArrayWrapper(pointer pArr, size_t ulSize)
        : m_pArr(pArr), m_ulSize(ulSize)
    {}

    template<typename T>
    const ArrayWrapper<typename T> & ArrayWrapper<T>::operator=(const ArrayWrapper & src)
    {
        m_pArr = src.m_pArr;
        m_ulSize = src.m_ulSize;
        return *this;
    }
    
    template<typename T>
    void ArrayWrapper<T>::swap(ArrayWrapper & src)
    {   swap(src.m_pArr, src.m_ulSize); }

    template<typename T>
    void ArrayWrapper<T>::swap(pointer & pArr, size_t& ulSize)
    {
        pointer pTmp = m_pArr;
        size_t ulSz = m_ulSize;

        m_pArr = pArr;
        m_ulSize = ulSize;

        pArr = pTmp;
        ulSize = ulSz;
    }

    template<typename T>
    ReadOnlyArray<T> GetReadOnlyReference(T* pArr, size_t ulSize)
    {
        return ReadOnlyArray<T>(pArr, ulSize);
    }

    template<typename T>
    ReadOnlyArray<T> GetReadOnlyReference(const WriteOnlyArray<T>& pArr)
    {
        return ReadOnlyArray<T>(static_cast<T*>(pArr.data()), pArr.size());
    }

    template<typename T>
    WriteOnlyArray<T> GetWritableOnlyReference(T* pArr, size_t ulSize)
    {
        return WriteOnlyArray<T>(pArr, ulSize);
    }

    template<typename T>
    WriteOnlyArray<T> GetWritableOnlyReference(const ReadOnlyArray<T>& pArr)
    {
        return WriteOnlyArray<T>(static_cast<T*>(pArr.data()), pArr.size());
    }
}
