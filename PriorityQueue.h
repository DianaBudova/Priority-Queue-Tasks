#pragma once
#include <iomanip>
template <typename T>
class PriorityQueueItem
{
private:
	T value;
	unsigned int priority;
public:
	PriorityQueueItem(T val, unsigned int pr)
	{
		value = val;
		priority = pr;
	}
	void SetData(T val)
	{
		value = val;
	}
	T GetData() const
	{
		return value;
	}
	void SetPriority(unsigned int pr)
	{
		priority = pr;
	}
	unsigned int GetPriority() const
	{
		return priority;
	}
	void Swap(PriorityQueueItem<T>& other)
	{
		/*value ^= other.value ^= value ^= other.value;
		priority ^= other.priority ^= priority ^= other.priority;*/
		T temp1 = value;
		value = other.value;
		other.value = temp1;
		unsigned int temp2 = priority;
		priority = other.priority;
		other.priority = temp2;
	}
};
template <typename T>
class PriorityQueue
{
	typedef bool(*PriorityQueuePredicate)(T obj);
private:
	static const int minBufferSize = 3;
	PriorityQueueItem<T>** buffer;
	size_t bufferSize;
	size_t count;
	bool CheckRules(size_t parent, size_t child)
	{
		return buffer[parent]->GetPriority() <= buffer[child]->GetPriority();
	}
	void ChangeBufferCapacity(size_t newSize)
	{
		PriorityQueueItem<T>** newBuffer = new PriorityQueueItem<T> *[newSize];
		memcpy(newBuffer, buffer, sizeof(size_t) * count);
		delete[] buffer;
		buffer = newBuffer;
		bufferSize = newSize;
	}
	void ExtendBuffer()
	{
		size_t newSize = bufferSize * 2;
		ChangeBufferCapacity(newSize);
	}
	void ShrinkBuffer()
	{
		if (count > bufferSize / 3)
			return;
		size_t newSize = bufferSize / 2;
		ChangeBufferCapacity(newSize);
	}
	bool IsInRange(size_t index)
	{
		return index >= 0 && index < count;
	}
	size_t ParentIndex(size_t index)
	{
		size_t result = index / 2;
		if (index % 2 == 0)
			result--;
		return result;
	}
	size_t LeftChildIndex(size_t index)
	{
		return 2 * index + 1;
	}
	size_t RightChildIndex(size_t index)
	{
		return 2 * index + 2;
	}
	void Swap(size_t left, size_t right)
	{
		buffer[left]->Swap(*buffer[right]);
	}
	void RemoveLast()
	{
		if (count < 1)
			return;
		delete buffer[count - 1];
		buffer[count - 1] = nullptr;
		count--;
	}
	void Normalize(size_t index)
	{
		if (!IsInRange(index))
			return;
		size_t next = -1;
		if (BubbleUp(index))
			next = ParentIndex(index);
		else if (BubbleDown(index))
			next = GetMinChildIndex(index);
		else
			return;
		Normalize(next);
	}
	bool BubbleUp(size_t index)
	{
		if (!IsInRange(index) || !IsInRange(ParentIndex(index)) || CheckRules(ParentIndex(index), index))
			return false;
		Swap(index, ParentIndex(index));
		return true;
	}
	bool BubbleDown(size_t index)
	{
		size_t child = GetMinChildIndex(index);
		if (!IsInRange(child) || CheckRules(index, child))
			return false;
		Swap(index, child);
		return true;
	}
	bool HasChildren(size_t index)
	{
		return IsInRange(index) && IsInRange(LeftChildIndex(index));
	}
	size_t GetMinChildIndex(size_t index)
	{
		if (!HasChildren(index))
			return -1;
		size_t leftChild = LeftChildIndex(index), rightChild = RightChildIndex(index);
		return (!IsInRange(rightChild)) ? leftChild : (buffer[rightChild]->GetPriority() < buffer[leftChild]->GetPriority()) ? rightChild : leftChild;
	}
public:
	PriorityQueue() : PriorityQueue(minBufferSize) {}
	PriorityQueue(size_t capacity)
	{
		bufferSize = (capacity > minBufferSize) ? capacity : minBufferSize;
		buffer = new PriorityQueueItem<T> *[bufferSize];
		count = 0;
	}
	~PriorityQueue()
	{
		if (!buffer)
			return;
		for (size_t i = 0; i < count; i++)
			delete buffer[i];
		delete[] buffer;
	}
	size_t GetCount()
	{
		return count;
	}
	void Add(T value, unsigned int pr)
	{
		if (count == bufferSize)
			ExtendBuffer();
		buffer[count++] = new PriorityQueueItem<T>(value, pr);
		Normalize(count - 1);
	}
	bool Poll()
	{
		if (count < 1)
			return false;
		Swap(0, count - 1);
		RemoveLast();
		Normalize(0);
		ShrinkBuffer();
		return true;
	}
	bool Head(T& value)
	{
		if (count < 1)
			return false;
		value = buffer[0]->GetData();
		return true;
	}
	size_t Search(T val)
	{
		for (size_t i = 0; i < count; i++)
			if (buffer[i]->GetData() == val)
				return i;
		return -1;
	}
	bool Remove(T val)
	{
		size_t rem;
		if ((rem = Search(val)) == -1)
			return false;
		Swap(rem, count - 1);
		RemoveLast();
		Normalize(rem);
		ShrinkBuffer();
		return true;
	}
	size_t All(T*& result, PriorityQueuePredicate pred)
	{
		size_t count_ = 0;
		T* temp = new T[this->count];
		for (size_t i = 0; i < this->count; i++)
			if (pred(this->buffer[i]->GetData())) //if(AnyName(this->buffer...
				temp[count_++] = this->buffer[i]->GetData();
		result = new T[count_];
		memcpy(result, temp, sizeof(T) * count_);
		delete[] temp;
		return count_;
	}
	friend std::ostream& operator<<(std::ostream& out, const PriorityQueue& obj)
	{
		for (size_t i = 0; i < obj.count; i++)
			out << "[" << std::setw(2) << i << ":" << std::setw(2) << obj.buffer[i]->GetData() << "]" << std::endl;
		return out;
	}
};