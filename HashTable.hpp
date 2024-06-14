#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace Close_Hash
{
	enum State { EMPTY, EXIST, DELETE };

	template<class K, class V>
	class HashTable
	{
		struct Elem
		{
			pair<K, V> _val;
			State _state;
		};

	public:
		HashTable(size_t size =10 )
		{
			_ht.resize(size);
			
		}

		// ≤Â»Î
		bool Insert(const pair<K, V>& val) {
			if (Find(val.first) != -1) {
				return false;
			}
			//¿©»›
			if (!Empty() && (_size * 10 / _ht.size()) > 7) {
				HashTable tmp(_ht.size() * 2);
				for (int i = 0;i<_ht.size();i++) {
					if (_ht[i]._state == EXIST) {
						tmp.Insert(_ht[i]._val);
					}
				}
				_ht.swap(tmp._ht);
			}

			//≤Â»Î ˝æ›
			K tmp = val.first % _ht.size();
			while (tmp < _size && _ht[tmp]._state) {  //—∞’“∑«ø’
				tmp++;
				tmp = tmp % _ht.size();
			}
			_ht[tmp]._val = val;
			_ht[tmp]._state = EXIST;
			_size++;
			return true;

		}
		void swap(HashTable h1, HashTable h2) {
			swap(h1._ht, h2._ht);
			swap(h1._size, h2._size);
		}
		// ≤È’“
		size_t Find(const K& key) {
			K tmp = key % _ht.size();
			while (tmp < _size && _ht[tmp]._state) {
				if (_ht[tmp]._val.first == key) {
					return tmp;
				}
				else {
					tmp++;
					tmp = tmp % _ht.size();
				}
			}
			return -1;
		}

		// …æ≥˝
		bool Erase(const K& key) {
			size_t hashi = Find(key);
			if (hashi == -1) {
				return false;
			}
			else {
				_ht[hashi]._state = DELETE;
			}
			_size--;
			return true;
		}

		size_t Size()const
		{
			return _size;
		}

		bool Empty() const
		{
			return _size == 0;
		}

		/*void Swap(HashTable<K, V>& ht)
		{
			swap(_size, ht._size);
			swap(_totalSize, ht._totalSize);
			_ht.swap(ht._ht);
		}*/

		

	private:
		vector<Elem> _ht;
		size_t _size=0;
		
	};
}