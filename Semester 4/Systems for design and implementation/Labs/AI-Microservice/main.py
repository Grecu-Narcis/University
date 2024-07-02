import os
import google.generativeai as genai

from fastapi import FastAPI
from pydantic import BaseModel


class RequestDTO(BaseModel):
    prompt: str


GOOGLE_API_KEY = os.environ['AI_KEY']
genai.configure(api_key=GOOGLE_API_KEY)
model = genai.GenerativeModel('gemini-1.5-flash')

app = FastAPI()


@app.get("/")
async def root():
    return {"message": "Hello World"}


@app.get("/hello/{name}")
async def say_hello(name: str):
    return {"message": f"Hi {name}! env is: {os.environ['AI_KEY']}"}


@app.post("/prompt")
async def get_response(request: RequestDTO):
    response = model.generate_content(request.prompt)

    return response.text
