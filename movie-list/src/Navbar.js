import {Component} from "react";
import styled from "styled-components";

const Nav=styled.div`
    height: 70%;
    background-Image: linear-gradient(120deg, #84fab0 0%, #8fd3f4 100%);
    display: flex;
    justify-Content: space-between;
    align-Items: center;
    position: relative,
`
class Navbar extends Component {
    render() {
        return (
            <>
                <div style={styles.navBar}>
                    <div style={styles.title}>
                        Movie List
                    </div>
                    <div style={styles.cartContainer}>
                        <img alt="cart-icon"
                             src="https://cdn-icons-png.flaticon.com/128/891/891462.png" style={styles.cartIcon} />
                        <span style={styles.cartCount}>3</span>
                    </div>
                </div>
            </>
        )
    }
}

export default Navbar;
const styles = {
    navBar: {
        height: 70,
        backgroundImage: "linear-gradient(120deg, #84fab0 0%, #8fd3f4 100%)",
        display: "flex",
        justifyContent: "space-between",
        alignItems: "center",
        position: "relative",
    },
    title: {
        fontSize: "30px",
        color: "#fff",
        fontWeight: "bold",
        fontFamily: '"Montserrat", sans-serif',
        textTransform: "uppercase",
        marginLeft: "20px",
        marginTop: "5px"
    },
    cartContainer: {
        position: 'relative',
        cursor: 'pointer',
    },
    cartIcon: {
        height: 48,
        marginRight: 20
    },
    cartCount: {
        backgroundColor: 'orange',
        borderRadius: "50%",
        paddingTop: "4px 8px",
        position: "absolute",
        right: 10,
        top: -5,
        fontSize: 12,
    }
}