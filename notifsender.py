import sys
from telebot import TeleBot

bot = TeleBot(str(sys.argv[1]))

bot.send_message(sys.argv[2], 'YOUR GAME WAS ACCEPTED!')


