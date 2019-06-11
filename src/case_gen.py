import sys

def main(*argv, **kwargs):
	morse = {}

	with open('src/morse.txt', 'r') as file:
		lines = file.readlines() 

		for line in lines:
			symbol, code = line.split()

			morse[symbol] = code

	morse[' '] = '/'

	amount = 0
	messages = []
	coded_messages = []

	message = input()

	while message:
		amount += 1

		messages.append(message)
		coded_messages.append(' '.join(map(morse.get, message)))

		message = input()

	print(amount)
	
	for coded_message in coded_messages:
		print(len(coded_message))
		print(coded_message)

	print()

	print(str('\n\n'.join(messages)))

if __name__ == '__main__':
	main()
