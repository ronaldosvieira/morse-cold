import sys

def main(*argv, **kwargs):
	morse = {}

	with open('src/morse.txt', 'r') as file:
		lines = file.readlines() 

		for line in lines:
			symbol, code = line.split()

			morse[symbol] = code

	morse[' '] = '/'

	messages = []
	coded_messages = []

	message = input()

	while message:
		messages.append(message)
		coded_messages.append(' '.join(map(morse.get, message)))

		message = input()
	
	for coded_message in coded_messages:
		print(coded_message)

if __name__ == '__main__':
	main()
