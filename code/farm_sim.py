import streamlit as st
import random

# ========== Session Initialization ==========
def init_state():
    defaults = {
        "animals": [],
        "day": 1,
        "wheat": {"planted": False, "days_left": 0, "watered": False, "stock": 0},
        "corn": {"planted": False, "days_left": 0, "watered": False, "stock": 0},
        "milk": 0,
        "eggs": 0,
        "money": 10.0,
        "auto_feed": False,
        "auto_water": False,
        "auto_harvest": False
    }
    for key, val in defaults.items():
        if key not in st.session_state:
            st.session_state[key] = val

init_state()

# ========== Farm Logic ==========
def feed_animal(index):
    animal = st.session_state.animals[index]
    gain = random.randint(5, 15)
    animal["health"] = min(100, animal["health"] + gain)
    animal["fed"] = True

    if animal["health"] > 50:
        animal["ready_to_produce"] = True
        st.success(f"Fed {animal['name']}, +{gain} health. Will produce tomorrow.")
    else:
        st.info(f"Fed {animal['name']}, +{gain} health.")

def plant_crop(crop):
    st.session_state[crop]["planted"] = True
    st.session_state[crop]["days_left"] = 3 if crop == "wheat" else 4
    st.session_state[crop]["watered"] = False
    st.success(f"Planted {crop.capitalize()}!")

def water_crop(crop):
    if st.session_state[crop]["planted"]:
        st.session_state[crop]["watered"] = True
        st.success(f"Watered {crop.capitalize()}!")
    else:
        st.warning(f"No {crop} planted.")

def harvest_crop(crop):
    if st.session_state[crop]["days_left"] == 0:
        if st.session_state[crop]["watered"]:
            yield_amount = random.randint(10, 20)
        else:
            yield_amount = random.randint(3, 8)
            st.warning(f"Low yield: {crop} wasn't watered.")
        st.session_state[crop]["stock"] += yield_amount
        st.session_state[crop]["planted"] = False
        st.success(f"Harvested {yield_amount} units of {crop}.")
    else:
        st.warning(f"{crop} isn't ready to harvest yet.")

# ========== Daily Simulation ==========
def new_day():
    st.session_state.day += 1
    st.balloons()

    surviving_animals = []
    for i, animal in enumerate(st.session_state.animals):
        if not animal["fed"]:
            if st.session_state.auto_feed:
                feed_animal(i)
            else:
                loss = random.randint(5, 15)
                animal["health"] = max(0, animal["health"] - loss)
                if animal["health"] == 0:
                    st.error(f"{animal['name']} has died due to not being fed.")
                    continue  # Skip this animal
                else:
                    st.warning(f"{animal['name']} not fed. Health -{loss}")
        animal["fed"] = False

        if animal["health"] > 0:
            surviving_animals.append(animal)

    st.session_state.animals = surviving_animals
    for animal in st.session_state.animals:
        if animal.get("ready_to_produce"):
            if animal["type"] == "Cow":
                milk = random.randint(1, 3)
                st.session_state.milk += milk
                st.toast(f"{animal['name']} produced {milk}L milk 🥛", icon="🐄")
            else:
                eggs = random.randint(1, 5)
                st.session_state.eggs += eggs
                st.toast(f"{animal['name']} laid {eggs} eggs 🥚", icon="🐔")
            animal["ready_to_produce"] = False  # Reset


    for crop in ["wheat", "corn"]:
        data = st.session_state[crop]
        if data["planted"] and data["days_left"] > 0:
            if st.session_state.auto_water:
                data["watered"] = True
            data["days_left"] -= 1

        if data["planted"] and data["days_left"] == 0 and st.session_state.auto_harvest:
            harvest_crop(crop)

    st.success(f"🌞 Day {st.session_state.day} started!")
    


# ========== Market ==========
def buy_item(item, qty, price):
    total = qty * price
    if st.session_state.money >= total:
        st.session_state.money -= total
        if item == "milk":
            st.session_state.milk += qty
        elif item == "eggs":
            st.session_state.eggs += qty
        elif item == "wheat":
            st.session_state.wheat["stock"] += qty
        elif item == "corn":
            st.session_state.corn["stock"] += qty
        st.success(f"Bought {qty} {item} for ${total:.2f}")
    else:
        st.error("Not enough money.")

def sell_item(item, qty, price):
    available = {
        "milk": st.session_state.milk,
        "eggs": st.session_state.eggs,
        "wheat": st.session_state.wheat["stock"],
        "corn": st.session_state.corn["stock"]
    }[item]

    if qty <= available:
        total = qty * price
        st.session_state.money += total
        if item == "milk":
            st.session_state.milk -= qty
        elif item == "eggs":
            st.session_state.eggs -= qty
        elif item == "wheat":
            st.session_state.wheat["stock"] -= qty
        elif item == "corn":
            st.session_state.corn["stock"] -= qty
        st.success(f"Sold {qty} {item} for ${total:.2f}")
    else:
        st.error(f"Not enough {item} in stock.")

# ========== Main UI ==========
def main():
    st.set_page_config(page_title="Farm Sim", layout="centered")
    st.title("🐄 Digital Farm Management System")

    # Sidebar
    with st.sidebar:
        st.header("📊 Farm Stats")
        st.write(f"Day: {st.session_state.day}")
        st.metric("Money", f"${st.session_state.money:.2f}")
        st.metric("Milk", f"{st.session_state.milk} L")
        st.metric("Eggs", st.session_state.eggs)
        st.metric("Wheat", st.session_state.wheat["stock"])
        st.metric("Corn", st.session_state.corn["stock"])
        if st.button("🌞 New Day"):
            new_day()

    # Tabs
    tab1, tab2, tab3, tab4 = st.tabs(["🐮 Animals", "🌱 Crops", "💰 Market", "👷 Workers"])

    # ========== Animals Tab ==========
    with tab1:
        st.subheader("🐮 Animal Management")
        with st.expander("➕ Add Animal"):
            name = st.text_input("Animal Name")
            animal_type = st.selectbox("Type", ["Cow", "Chicken"])
            if st.button("Add Animal"):
                if name:
                    st.session_state.animals.append({
                        "name": name,
                        "type": animal_type,
                        "health": 100,
                        "fed": False
                    })
                    st.success(f"{animal_type} '{name}' added!")
                else:
                    st.warning("Please enter a name.")

        if not st.session_state.animals:
            st.info("No animals yet.")
        else:
            for i, a in enumerate(st.session_state.animals):
                col1, col2 = st.columns([4, 1])
                with col1:
                    st.progress(
                        a["health"] / 100,
                        text=f"{a['name']} ({a['type']}) - Health: {a['health']}/100"
                    )
                with col2:
                    if st.button("Feed", key=f"feed_{i}"):
                        feed_animal(i)

    # ========== Crops Tab ==========
    with tab2:
        st.subheader("🌾 Crop Management")
        for crop in ["wheat", "corn"]:
            data = st.session_state[crop]
            with st.container():
                st.markdown(f"### {crop.capitalize()}")
                if data["planted"]:
                    if data["days_left"] > 0:
                        st.progress(
                            1 - (data["days_left"] / (3 if crop == "wheat" else 4)),
                            text=f"Growing ({data['days_left']} days left)"
                        )
                        if st.button(f"💧 Water {crop.capitalize()}", key=f"water_{crop}"):
                            water_crop(crop)
                    else:
                        st.success(f"{crop.capitalize()} is ready!")
                        if st.button(f"🌾 Harvest {crop.capitalize()}", key=f"harvest_{crop}"):
                            harvest_crop(crop)
                else:
                    if st.button(f"🌱 Plant {crop.capitalize()}", key=f"plant_{crop}"):
                        plant_crop(crop)

    # ========== Market Tab ==========
    with tab3:
        st.subheader("💰 Market")

        tab_buy, tab_sell = st.tabs(["Buy", "Sell"])

        with tab_buy:
            item = st.selectbox("Buy Item", ["milk", "eggs", "wheat", "corn"], key="buy_item")
            qty = st.slider("Quantity", 1, 100, 5)
            price = st.select_slider("Price", [1.0, 1.5, 2.0, 2.5, 3.0], value=2.0)
            if st.button("Purchase"):
                buy_item(item, qty, price)

        with tab_sell:
            item = st.selectbox("Sell Item", ["milk", "eggs", "wheat", "corn"], key="sell_item")
            available = {
                "milk": st.session_state.milk,
                "eggs": st.session_state.eggs,
                "wheat": st.session_state.wheat["stock"],
                "corn": st.session_state.corn["stock"]
            }[item]

            st.write(f"Available: {available}")
            if available > 0:
                if available > 1:
                    qty = st.slider("Sell Quantity", 1, available, min(5, available))
                else:
                    qty = 1  # default to 1 if only one unit is available

                price = st.select_slider("Price", [0.5, 1.0, 1.5, 2.0], value=1.0)
                if st.button("Sell"):
                    sell_item(item, qty, price)
            else:
                st.warning(f"No {item} to sell.")

    # ========== Worker Tab ==========
    with tab4:
        st.subheader("👷 Worker Roles")
        st.checkbox("Auto Feed Animals", key="auto_feed")
        st.checkbox("Auto Water Crops", key="auto_water")
        st.checkbox("Auto Harvest Crops", key="auto_harvest")
        st.info("Workers perform tasks automatically at day start.")

if __name__ == "__main__":
    main()
