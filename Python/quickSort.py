def quicksort(arr, left, right):
    if left < right:
        pi = partition(arr, left, right)
        quicksort(arr, left, pi-1)
        quicksort(arr, pi+1, right)


def partition(arr, left, right):
    pivot = arr[right]
    i = left - 1

    for j in range(left, right):
        if arr[j] <= pivot:
            i += 1
            arr[j], arr[i] = arr[i], arr[j]

    arr[i+1], arr[right] = arr[right], arr[i+1]
    return i+1

if __name__ == "__main__":
    arr = [3,5,34,657,34,23,54,3,123,0,12,43,4,54,3,2,4,5656,121]
    print(arr)

    quicksort(arr, 0, len(arr)-1)
    print(arr)
