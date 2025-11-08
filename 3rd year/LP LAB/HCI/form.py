import streamlit as st

# Page setup
st.set_page_config(page_title="Feedback Portal", layout="centered")
st.sidebar.title("🔍 Navigation")

# Initialize a variable to track the current page
if "page" not in st.session_state:
    st.session_state.page = "Home"

# Navigation using buttons
if st.sidebar.button("🏠 Home"):
    st.session_state.page = "Home"
if st.sidebar.button("📝 Feedback Form"):
    st.session_state.page = "Feedback Form"
if st.sidebar.button("📊 Summary"):
    st.session_state.page = "Summary"

# ------------------ SESSION STATE ------------------
if "name" not in st.session_state:
    st.session_state.name = ""
if "age" not in st.session_state:
    st.session_state.age = 1
if "feedback" not in st.session_state:
    st.session_state.feedback = ""

# ------------------ PAGE 1: HOME ------------------
if st.session_state.page == "Home":
    st.title("🏠 Welcome to the Feedback Portal")
    st.write("""
    This is a simple **multi-page Streamlit app** with navigation buttons.
    Use the sidebar to move between pages.
    """)
    st.image("https://cdn-icons-png.flaticon.com/512/295/295128.png", width=120)
    st.info("➡️ Click on **Feedback Form** from the sidebar to begin.")

# ------------------ PAGE 2: FEEDBACK FORM ------------------
elif st.session_state.page == "Feedback Form":
    st.title("📝 Feedback Form")

    with st.form("feedback_form"):
        st.subheader("Enter your details below:")

        name = st.text_input("Name", st.session_state.name)
        age = st.number_input("Age", min_value=1, max_value=120, step=1, value=max(1, st.session_state.age))
        feedback = st.text_area("Your Feedback", st.session_state.feedback)

        submitted = st.form_submit_button("Submit")

    if submitted:
        if name and feedback:
            st.session_state.name = name
            st.session_state.age = age
            st.session_state.feedback = feedback
            st.success("✅ Feedback submitted successfully!")
            st.balloons()
        else:
            st.warning("⚠️ Please fill all fields before submitting.")

# ------------------ PAGE 3: SUMMARY ------------------
elif st.session_state.page == "Summary":
    st.title("📊 Submission Summary")

    if st.session_state.name and st.session_state.feedback:
        st.success(f"✅ Thank you, **{st.session_state.name}**!")
        st.write(f"**Age:** {st.session_state.age}")
        st.write(f"**Feedback:** {st.session_state.feedback}")
        st.write("---")
        st.info("You can go back to the Feedback Form to edit your response.")
    else:
        st.warning("⚠️ No feedback submitted yet. Go to the 'Feedback Form' page first.")