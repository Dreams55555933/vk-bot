import vk_api
from pydantic.color import Color
from vk_api.keyboard import VkKeyboard, VkKeyboardColor
from vk_api.longpoll import VkLongPoll,VkEventType

from config import BOT_TOKEN, AI_TOKEN

session = vk_api.VkApi(token=BOT_TOKEN)


def send_message(user_id,message,keyboard=None):
    post = {
            "user_id":user_id,
            "message":message,
            "random_id":0,
    }
    if keyboard is not None:
        post["keyboard"] = keyboard.get_keyboard()

    session.method("messages.send",post)


for event in VkLongPoll(session).listen():
    if event.type == VkEventType.MESSAGE_NEW and event.to_me:
        message:str = event.message.lower()
        user_id = event.user_id
        print(user_id)
        if message=="start" or message=="начать":

            send_message(
                user_id=user_id,
                message="Напиши вопрос нейросети ChatGPT-nano",
            )
        else:
            from openai import OpenAI

            client = OpenAI(
                api_key=AI_TOKEN,  # Ключ из нашего сервиса
                base_url="https://api.aitunnel.ru/v1/",
            )

            chat_result = client.chat.completions.create(
                messages=[{"role": "user", "content": message}],
                model="gpt-4.1-nano",
                max_tokens=50000,  # Старайтесь указывать для более точного расчёта цены
            )
            print(chat_result.choices[0].message)
            send_message(user_id=user_id,message=chat_result.choices[0].message.content)
