from PIL import Image, ImageEnhance
import matplotlib.pyplot as plt
import numpy as np
import os


def apply_vintage_filter(image_path, output_path="vintage_image.png"):
    try:
        # Open the image
        img = Image.open(image_path).convert("RGB")

        # Resize for consistency (optional, can be removed)
        img_resized = img.resize((128, 128))

        # --- Step 1: Apply sepia tone ---
        sepia = np.array(img_resized)
        r, g, b = sepia[:,:,0], sepia[:,:,1], sepia[:,:,2]
        tr = 0.393 * r + 0.769 * g + 0.189 * b
        tg = 0.349 * r + 0.686 * g + 0.168 * b
        tb = 0.272 * r + 0.534 * g + 0.131 * b
        sepia[:,:,0] = np.clip(tr, 0, 255)
        sepia[:,:,1] = np.clip(tg, 0, 255)
        sepia[:,:,2] = np.clip(tb, 0, 255)
        img_sepia = Image.fromarray(sepia.astype('uint8'))

        # --- Step 2: Reduce contrast and brightness ---
        enhancer_contrast = ImageEnhance.Contrast(img_sepia)
        img_low_contrast = enhancer_contrast.enhance(0.85)  # less contrast
        enhancer_brightness = ImageEnhance.Brightness(img_low_contrast)
        img_faded = enhancer_brightness.enhance(0.95)       # slightly darker

        # --- Step 3: Add noise/grain ---
        np_img = np.array(img_faded)
        noise = np.random.normal(0, 15, np_img.shape).astype(np.int16)  # Gaussian noise
        noisy_img = np_img.astype(np.int16) + noise
        noisy_img = np.clip(noisy_img, 0, 255).astype(np.uint8)
        img_final = Image.fromarray(noisy_img)

        # --- Step 4: Display and save ---
        plt.imshow(img_final)
        plt.axis('off')
        plt.savefig(output_path, bbox_inches='tight', pad_inches=0)
        plt.close()

        print(f"Processed image saved as '{output_path}'.")

    except Exception as e:
        print(f"Error processing image: {e}")


# Run interactively
if __name__ == "__main__":
    print("Vintage Photo Processor (type 'exit' to quit)\n")
    while True:
        image_path = input("Enter image filename (or 'exit' to quit): ").strip()
        if image_path.lower() == 'exit':
            print("Goodbye!")
            break
        if not os.path.isfile(image_path):
            print(f"File not found: {image_path}")
            continue
        base, ext = os.path.splitext(image_path)
        output_file = f"{base}_vintage{ext}"
        apply_vintage_filter(image_path, output_file)
