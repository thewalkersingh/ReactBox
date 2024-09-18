import {Component} from "react";

export default class MovieCard extends Component {

    render() {
        console.log(this.props);
        const {movies, addStars, decStars, toggleFav, toggleCart} = this.props;
        const {title, plot, price, rating, stars, fav, poster, isInCart} = this.props.movies;
        return (
            <div className="main">
                <div className="movie-card">
                    <div className="left">
                        <img
                            src={poster}
                            alt="Movie Poster" />
                    </div>
                    <div className={"right"}>
                        <div className={"title"}> {title}</div>
                        <div className={"plot"}>{plot}</div>
                        <div className={"price"}>Rs. {price}</div>
                        <div className={"footer"}>
                            <div className={"rating"}>{rating}</div>
                            <div className="star-dis">
                                <img className="str-btn" alt="decrease"
                                     src="https://cdn-icons-png.flaticon.com/128/9068/9068779.png"
                                     onClick={() => {
                                         decStars(movies)
                                     }} />
                                <img className="stars" alt="star"
                                     src="https://cdn-icons-png.flaticon.com/128/2107/2107957.png" />
                                <img className="str-btn" alt="increase"
                                     src="https://cdn-icons-png.flaticon.com/128/1828/1828817.png"
                                     onClick={() => {
                                         addStars(movies)
                                     }} />
                                <span className="starCount">&nbsp;{stars}</span>
                            </div>

                            {/*{fav ? <button className={"unfavourite-btn"} onClick={this.handleFav}>Un-Favourite</button>*/}
                            {/*    : <button className={"favourite-btn"} onClick={this.handleFav}>Favourite</button>}*/}
                            {/* conditional rending on className*/}

                            <button className={fav ? "favourite-btn" : "unfavourite-btn"}
                                    onClick={() => {
                                        toggleFav(movies)
                                    }}>{fav ? "Favourite" : "Un-Favorite"}
                            </button>

                            <button className={isInCart ? "cart-btn-add" : "cart-btn-remove"}
                                    onClick={() => {
                                        toggleCart(movies)
                                    }}>{isInCart ? "Add" : "Remove"}</button>
                        </div>
                    </div>
                </div>
            </div>
        )
    }
}