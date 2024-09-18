import {Component} from "react";
import MovieCard from "./MovieCard";

export default class MovieList extends Component {
    constructor() {
        super();
        this.state = {
            movies: [{
                id: 1,
                title: "The Avengers", plot: "Super heroes joins the team to save the earth",
                poster: "https://image.tmdb.org/t/p/original/yHdPTs239Cqce1s6y9figbeolR1.jpg", price: 199, rating: 8.9,
                stars: 0, fav: true, kart: true
            }, {
                id: 2,
                title: "Thor", plot: "Thor is banished from Asguard",
                poster: "https://image.tmdb.org/t/p/original/yHdPTs239Cqce1s6y9figbeolR1.jpg", price: 190, rating: 8.,
                stars: 0, fav: false, kart: false
            }, {
                id: 3,
                title: "Captain America", plot: "Captain America wakes up after 70 years",
                poster: "https://image.tmdb.org/t/p/original/yHdPTs239Cqce1s6y9figbeolR1.jpg", price: 189, rating: 8.5,
                stars: 0, fav: true, kart: true
            }]
        }
    }

    handleIncStar = (movie) => {
        const {movies} = this.state;
        const movieId = movies.indexOf(movie);
        if (movies[movieId].stars >= 10) return;
        movies[movieId].stars += 0.5;
        this.setState({
            movies: movies
        })
    }
    handleDecStars = (movie) => {
        const {movies} = this.state;
        const movieId = movies.indexOf(movie);
        if (movies[movieId].stars >= 10) return;
        movies[movieId].stars -= 0.5;
        this.setState({
            movies: movies
        })
    }
    handelToggleFav = (movie) => {
        const {movies} = this.state;
        const mid = movies.indexOf(movie);
        movies[mid].fav = !movies[mid].fav;
        this.setState({
            movies: movies
        })
    }
    handleToggleCart = (movie) => {
        const {movies} = this.state;
        const mid = movies.indexOf(movie);
        movies[mid].isInCart = !movies[mid].isInCart;
        this.setState({
            movies: movies
        })
    }

    render() {
        // const {title, plot, price, rating, stars, fav, kart,poster} = this.state.movies;
        const {movies} = this.state;
        return (<>
            {movies.map((movie) => <MovieCard movies={movie}
                                              addStars={this.handleIncStar}
                                              decStars={this.handleDecStars}
                                              toggleFav={this.handelToggleFav}
                                              toggleCart={this.handleToggleCart}
                                              key={movie.id}
            />)}
        </>)
    }
}