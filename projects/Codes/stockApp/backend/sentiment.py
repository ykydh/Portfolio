from transformers import AutoTokenizer, AutoModelForSequenceClassification
import torch
import numpy as np

finbert_model = AutoModelForSequenceClassification.from_pretrained("yiyanghkust/finbert-tone")
finbert_tokenizer = AutoTokenizer.from_pretrained("yiyanghkust/finbert-tone")

labels = ["Neutral", "Positive", "Negative"]  # correct order

device = "cuda" if torch.cuda.is_available() else "cpu"
finbert_model.to(device)

def analyze_sentiment(text):
    if not text or not text.strip():
        return 0.0  # Neutral
    inputs = finbert_tokenizer(
        text,
        return_tensors="pt",
        truncation=True,
        max_length=512
    ).to(device)

    with torch.no_grad():
        outputs = finbert_model(**inputs)

    logits = outputs.logits
    probabilities = torch.softmax(logits, dim=1).cpu().numpy()[0]


    max_index = np.argmax(probabilities)
    sentiment_label = labels[max_index]
    confidence = float(probabilities[max_index])

    # Convert to signed score: Positive -> +, Negative -> -, Neutral -> 0
    if sentiment_label == "Positive":
        score = confidence
    elif sentiment_label == "Negative":
        score = -confidence
    else:  
        score = 0.0

    return confidence, score

