import sys

n = 10

def binSearch(n):
	prev_mid = 0
	low = 0
	high = n
	mid = n/2

	while (prev_mid*100) // 1 != (mid*100)//1:
		if mid * mid < n:
			low = mid
			high= high	
		elif mid * mid > n:
			low = low
			high= mid
		else:
			return mid
		prev_mid = mid
		mid = (low+high)/2

	return round(mid,2)

print(binSearch(int(sys.argv[1])))
