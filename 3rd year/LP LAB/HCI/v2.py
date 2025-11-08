import streamlit as st

# ------------------ PAGE SETUP ------------------
st.set_page_config(page_title="Feedback Portal", layout="centered")
st.sidebar.title("Navigation")

# ------------------ NAVIGATION STATE ------------------
if "page" not in st.session_state:
    st.session_state.page = "Home"

if st.sidebar.button("Home"):
    st.session_state.page = "Home"
    st.toast("Returning Home...")
if st.sidebar.button("Feedback Form"):
    st.session_state.page = "Feedback Form"
    st.toast("Opening Feedback Form...")
if st.sidebar.button("Summary"):
    st.session_state.page = "Summary"
    st.toast("Viewing Summary...")
    st.snow()

# ------------------ SESSION STATE VARIABLES ------------------
if "name" not in st.session_state:
    st.session_state.name = ""
if "age" not in st.session_state:
    st.session_state.age = 5  
if "feedback" not in st.session_state:
    st.session_state.feedback = ""
if "course" not in st.session_state:
    st.session_state.course = ""
if "rating" not in st.session_state:
    st.session_state.rating = ""

# ------------------ PAGE 1: HOME ------------------
    if st.session_state.page == "Home":
        st.title("Welcome to the Feedback Portal")
        st.write("""
        This is a simple **multi-page Streamlit app** with navigation buttons.
        Use the sidebar to move between pages.
        """)
        st.markdown("###  We value your feedback!")
        st.info(" Click on **Feedback Form** from the sidebar to begin.")

# ------------------ PAGE 2: FEEDBACK FORM ------------------
elif st.session_state.page == "Feedback Form":
    st.title("Feedback Form")

    with st.form("feedback_form"):
        st.subheader("Enter your details below:")
        name = st.text_input("Name", st.session_state.name)
        age = st.number_input("Age", min_value=5, max_value=100, step=1, value=st.session_state.age)     
        course = st.selectbox("Course", ["B.Tech", "B.Sc", "BCA", "MCA", "MBA"])
        rating = st.selectbox("Rate our session", ["Excellent", "Good", "Average", "Poor"])
        feedback = st.text_area("Your Feedback", st.session_state.feedback, height=120)

        # ✅ Submit button inside form
        submitted = st.form_submit_button("Submit")

    # Form submission handling
    if submitted:
        if name and feedback:
            st.session_state.name = name
            st.session_state.age = age
            st.session_state.course = course
            st.session_state.rating = rating
            st.session_state.feedback = feedback
            st.success("Feedback submitted successfully!")
            
            st.balloons()
        else:
            st.warning("Please fill all fields before submitting.")

# ------------------ PAGE 3: SUMMARY ------------------
elif st.session_state.page == "Summary":
    st.title("Submission Summary")

    if st.session_state.name and st.session_state.feedback:
        st.success(f"Thank you, **{st.session_state.name}**!")
        st.write(f"**Age:** {st.session_state.age}")
        st.write(f"**Course:** {st.session_state.course}")
        st.write(f"**Rating:** {st.session_state.rating}")
        st.write(f"**Feedback:** {st.session_state.feedback}")
        st.write("---")
        st.info("You can go back to the Feedback Form to edit your response.")
    else:
        st.warning("No feedback submitted yet. Go to the 'Feedback Form' page first.")
