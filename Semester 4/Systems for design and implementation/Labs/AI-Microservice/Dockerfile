FROM ubuntu:latest
FROM python:3.10

WORKDIR /app

COPY requirements.txt .
COPY main.py .

RUN pip install  --no-cache-dir -r requirements.txt
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]