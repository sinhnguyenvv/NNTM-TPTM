import tensorflow as tf
from tensorflow.keras.models import load_model
import numpy as np
import cv2
import os

# Tải mô hình đã huấn luyện
model = load_model('model/model.h5')

# Danh sách nhãn
class_names = ['unripe', 'ripe']

# Hàm xử lý ảnh
def preprocess_image(image_path):
    img = cv2.imread(image_path)
    img = cv2.resize(img, (224, 224))  # Resize theo input model
    img = img / 255.0
    img = np.expand_dims(img, axis=0)
    return img

# Dự đoán ảnh đầu vào
def predict(image_path):
    image = preprocess_image(image_path)
    prediction = model.predict(image)
    class_index = np.argmax(prediction)
    confidence = np.max(prediction)
    return class_names[class_index], confidence

# Thực thi
if __name__ == "__main__":
    input_path = 'images/test.jpg'  # Đổi ảnh tại đây
    label, conf = predict(input_path)
    print(f"Ảnh: {input_path} → Kết quả: {label.upper()} ({conf*100:.2f}%)")
