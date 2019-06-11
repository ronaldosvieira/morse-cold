import sys

def main(*argv, **kwargs):
	morse = {}

	with open('src/morse.txt', 'r') as file:
		lines = file.readlines() 

		for line in lines:
			symbol, code = line.split()

			morse[symbol] = code

	morse[' '] = '/'

	amount = int(input())

	print(amount)

	for _ in range(amount):
		message = input()

		coded_message = ' '.join(map(morse.get, message))

		print(len(coded_message))
		print(coded_message)

if __name__ == '__main__':
	main()
